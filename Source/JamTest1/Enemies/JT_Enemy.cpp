// Fill out your copyright notice in the Description page of Project Settings.


#include "JT_Enemy.h"

#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
AJT_Enemy::AJT_Enemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MainCollision = CreateDefaultSubobject<UCapsuleComponent>("MainCollision");
	RootComponent = MainCollision;

	DamageComponent = CreateDefaultSubobject<UDamageComponent>(TEXT("DamageComponent"));
	DamageComponent->MaxHealth = 100.;
	ImpulseComponent = CreateDefaultSubobject<UImpulseComponent>(TEXT("ImpulseComponent"));
	ImpulseComponent->ImpulseTime = .5;
	ImpulseComponent->SetActor(this);
	HealthBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarWidget"));
	HealthBarWidget->SetupAttachment(RootComponent);
}

void AJT_Enemy::TargetPlayer_Implementation(AActor* Player)
{
}

// Called when the game starts or when spawned
void AJT_Enemy::BeginPlay()
{
	Super::BeginPlay();
	DamageComponent->SetHealthBarWidget(Cast<UCharacterHealthBar>(HealthBarWidget->GetUserWidgetObject()));
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

void AJT_Enemy::TakeDamage_Implementation(AActor* From, float Damage)
{
	ImpulseComponent->AddImpulse(From, Damage);
	DamageComponent->TakeDamage(Damage);
}

