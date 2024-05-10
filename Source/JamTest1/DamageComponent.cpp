// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageComponent.h"

// Sets default values for this component's properties
UDamageComponent::UDamageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	MaxHealth = 100.f;
	CurrentHealth = MaxHealth;
}


// Called when the game starts
void UDamageComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UDamageComponent::TakeDamage(float Damage)
{
	CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.0f, MaxHealth);
	OnSetHealthDelegate.ExecuteIfBound(CurrentHealth / MaxHealth);
}


void UDamageComponent::Heal(float Heal)
{
	CurrentHealth = FMath::Min(CurrentHealth + Heal, MaxHealth);
	OnSetHealthDelegate.ExecuteIfBound(CurrentHealth / MaxHealth);
}


float UDamageComponent::GetHealthPercent()
{
	return (MaxHealth > 0) ? (CurrentHealth / MaxHealth) : 0;
}


bool UDamageComponent::IsDead()
{
	return CurrentHealth <= 0;
}
