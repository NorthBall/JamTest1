// Fill out your copyright notice in the Description page of Project Settings.


#include "JT_Enemy.h"

#include "Components/CapsuleComponent.h"

// Sets default values
AJT_Enemy::AJT_Enemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MainCollision = CreateDefaultSubobject<UCapsuleComponent>("MainCollision");
	RootComponent = MainCollision;
}

void AJT_Enemy::TargetPlayer_Implementation(AActor* Player)
{
}

// Called when the game starts or when spawned
void AJT_Enemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJT_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AJT_Enemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

