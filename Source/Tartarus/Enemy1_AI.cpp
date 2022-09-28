// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy1_AI.h"

// Sets default values
AEnemy1_AI::AEnemy1_AI()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemy1_AI::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy1_AI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy1_AI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

