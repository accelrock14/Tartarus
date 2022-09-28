// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Spider_AI.generated.h"

UCLASS()
class TARTARUS_API ASpider_AI : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASpider_AI();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	float Speed = 20.0f;

	UPROPERTY(EditAnywhere)
	float TravelDistance = 5.0f;

	UPROPERTY(VisibleDefaultsOnly)
	class UBoxComponent *DamageCollision;

	UPROPERTY(EditAnywhere)
	float DamageValue = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Health = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxHealth = 100.0f;

	UFUNCTION()
	void OnHit(UPrimitiveComponent *HitComp, AActor *OtherActor,
			   UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &Hit);

	UFUNCTION()
	void ShootProjectile();

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AProjectile> Projectile;

	class UWorld *World;
	FRotator SpawnRotation;

private:
	bool isGoingUp;
	bool isGoingDown;

	FVector TargetLocation;
	FVector StartLocation;
	FVector CurrentLocation;

	FTimerHandle ShootTimer;
	FVector SpawnLocation;
};
