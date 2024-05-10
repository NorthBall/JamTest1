// Fill out your copyright notice in the Description page of Project Settings.


#include "JT_NeutralEntity.h"

#include "Components/WidgetComponent.h"
#include "JamTest1/DamageComponent.h"
#include "JamTest1/JT_GameState.h"

AJT_NeutralEntity::AJT_NeutralEntity()
{
	bRegisteredInGameState = false;
	bIsKeyPoint = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	
	DamageComponent = CreateDefaultSubobject<UDamageComponent>(TEXT("DamageComponent"));
	DamageComponent->MaxHealth = 100.;
	HealthBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarWidget"));
	HealthBarWidget->SetupAttachment(RootComponent);
}

UDamageComponent* AJT_NeutralEntity::GetDamageComponent_Implementation()
{
	return DamageComponent;
}

void AJT_NeutralEntity::TakeDamage_Implementation(AActor* From, float Damage)
{
	DamageComponent->TakeDamage(Damage);

	if (DamageComponent->IsDead())
	{
		OnDeath();
	}
}

void AJT_NeutralEntity::AddImpulse_Implementation(AActor* From, float Impulse)
{
}

void AJT_NeutralEntity::BeginPlay()
{
	Super::BeginPlay();
	
	UCharacterHealthBar* CharacterHealth = Cast<UCharacterHealthBar>(HealthBarWidget->GetUserWidgetObject());
	if (IsValid(CharacterHealth)) {
		DamageComponent->OnSetHealthDelegate.BindDynamic(CharacterHealth, &UCharacterHealthBar::OnSetHealth);
		DamageComponent->OnSetHealthDelegate.ExecuteIfBound(DamageComponent->GetHealthPercent());
	}

	RegisterInGameState();
}

void AJT_NeutralEntity::OnDeath_Implementation()
{
	UnregisterFromGameState();
	Destroy();
}

void AJT_NeutralEntity::RegisterInGameState()
{
	if(!bIsKeyPoint)
	{
		return;
	}
	
	if (!IsValid(GetWorld()))
	{
		return;
	}

	auto GameState = GetWorld()->GetGameState<AJT_GameState>();
	if(!IsValid(GameState))
	{
		return;
	}

	GameState->RegisterKeyPoint();
	bRegisteredInGameState = true;
}

void AJT_NeutralEntity::UnregisterFromGameState()
{
	if(!bIsKeyPoint
		||!bRegisteredInGameState)
	{
		return;
	}

	if (!IsValid(GetWorld()))
	{
		return;
	}

	auto GameState = GetWorld()->GetGameState<AJT_GameState>();
	if(!IsValid(GameState))
	{
		return;
	}

	GameState->UnregisterKeyPoint();
	bRegisteredInGameState = false;
}
