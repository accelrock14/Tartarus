// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spike.generated.h"

UCLASS()
class TARTARUS_API ASpike : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpike();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleDefaultsOnly)
	class UBoxComponent *DamageCollision;

	UPROPERTY(EditAnywhere)
	float DamageValue = 20.0f;

	UPROPERTY(EditAnywhere)
	FVector SpawnLocation;

	UFUNCTION()
	void OnHit(UPrimitiveComponent *HitComp, AActor *OtherActor,
			   UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &Hit);
};
