// Fill out your copyright notice in the Description page of Project Settings.

#include "Spider_AI.h"
#include "Components/BoxComponent.h"
#include "TartarusCharacter.h"
#include "Engine/World.h"

#include "Projectile.h"
#include "Kismet/GameplayStatics.h"

#include "TartarusGameMode.h"

// Sets default values
ASpider_AI::ASpider_AI()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DamageCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Damage Collision"));
	DamageCollision->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASpider_AI::BeginPlay()
{
	Super::BeginPlay();

	DamageCollision->OnComponentBeginOverlap.AddDynamic(this, &ASpider_AI::OnHit);
	World = GetWorld();

	CurrentLocation = this->GetActorLocation();
	StartLocation = this->GetActorLocation();
	TargetLocation.Z = StartLocation.Z + TravelDistance;
	isGoingUp = true;
	isGoingDown = false;

	GetWorld()->GetTimerManager().SetTimer(ShootTimer, this, &ASpider_AI::ShootProjectile, 2.0f, true);
}

// Called every frame
void ASpider_AI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// move actor upwards
	if (TargetLocation.Z > CurrentLocation.Z && isGoingUp)
	{
		CurrentLocation.Z += Speed * DeltaTime;

		SetActorLocation(CurrentLocation);
		if (TargetLocation.Z <= CurrentLocation.Z)
		{
			isGoingDown = true;
			isGoingUp = false;
		}
	}
	// move actor downwards
	if (StartLocation.Z < CurrentLocation.Z && isGoingDown)
	{
		CurrentLocation.Z -= Speed * DeltaTime;

		SetActorLocation(CurrentLocation);
		if (StartLocation.Z >= CurrentLocation.Z)
		{
			isGoingDown = false;
			isGoingUp = true;
		}
	}
}

// Called to bind functionality to input
void ASpider_AI::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ASpider_AI::OnHit(UPrimitiveComponent *HitComp, AActor *OtherActor,
					   UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &Hit)
{
	ATartarusCharacter *Char = Cast<ATartarusCharacter>(OtherActor);

	if (Char)
	{
		Char->DealDamage(DamageValue);
	}
}

void ASpider_AI::ShootProjectile()
{
	if (World != NULL)
	{
		SpawnRotation = GetControlRotation();

		SpawnLocation = CurrentLocation;
		SpawnLocation.Y -= 50.0f;

		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		World->SpawnActor<AProjectile>(Projectile, SpawnLocation, SpawnRotation, ActorSpawnParams);
	}
}
