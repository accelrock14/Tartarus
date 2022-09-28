// Fill out your copyright notice in the Description page of Project Settings.

#include "Bug_AI.h"
#include "Components/BoxComponent.h"
#include "Misc/App.h"
#include "TartarusCharacter.h"

// Sets default values
ABug_AI::ABug_AI()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DamageCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Damage Collision"));
	DamageCollision->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABug_AI::BeginPlay()
{
	Super::BeginPlay();

	DamageCollision->OnComponentBeginOverlap.AddDynamic(this, &ABug_AI::OnHit);
	CurrentLocation = this->GetActorLocation();
	StartLocation = this->GetActorLocation();
	TargetLocation.Y = StartLocation.Y + TravelDistance;
	isGoingForward = true;
	isGoingBackward = false;
}

// Called every frame
void ABug_AI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (TargetLocation.Y >= CurrentLocation.Y && isGoingForward)
	{
		CurrentLocation.Y += Speed * DeltaTime;

		SetActorLocation(CurrentLocation);
		if (TargetLocation.Y <= CurrentLocation.Y)
		{
			isGoingBackward = true;
			isGoingForward = false;

			FRotator NewRotation = FRotator(0.0f, 180.0f, 0.0f);

			FQuat QuatRotation = FQuat(NewRotation);

			AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
		}
	}
	if (StartLocation.Y <= CurrentLocation.Y && isGoingBackward)
	{
		CurrentLocation.Y -= Speed * DeltaTime;

		SetActorLocation(CurrentLocation);
		if (StartLocation.Y >= CurrentLocation.Y)
		{
			isGoingBackward = false;
			isGoingForward = true;

			FRotator NewRotation = FRotator(0.0f, 180.0f, 0.0f);

			FQuat QuatRotation = FQuat(NewRotation);

			AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
		}
	}
}

// Called to bind functionality to input
void ABug_AI::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABug_AI::OnHit(UPrimitiveComponent *HitComp, AActor *OtherActor,
					UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &Hit)
{
	ATartarusCharacter *Char = Cast<ATartarusCharacter>(OtherActor);

	if (Char)
	{
		Char->DealDamage(DamageValue);
	}
}

void ABug_AI::Patrol()
{
}
