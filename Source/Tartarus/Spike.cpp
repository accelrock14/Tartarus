// Fill out your copyright notice in the Description page of Project Settings.

#include "Spike.h"
#include "Components/BoxComponent.h"
#include "TartarusCharacter.h"

// Sets default values
ASpike::ASpike()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DamageCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Damage Collision"));
	DamageCollision->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASpike::BeginPlay()
{
	Super::BeginPlay();

	DamageCollision->OnComponentBeginOverlap.AddDynamic(this, &ASpike::OnHit);
}

// Called every frame
void ASpike::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpike::OnHit(UPrimitiveComponent *HitComp, AActor *OtherActor,
				   UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &Hit)
{
	ATartarusCharacter *Char = Cast<ATartarusCharacter>(OtherActor);

	if (Char)
	{
		Char->DealDamage(DamageValue);
	}
	if (Char->Health > 0)
	{
		Char->SetActorLocation(SpawnLocation);
	}
}
