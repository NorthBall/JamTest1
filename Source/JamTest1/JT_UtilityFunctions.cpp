// Fill out your copyright notice in the Description page of Project Settings.


#include "JT_UtilityFunctions.h"

void UJT_UtilityFunctions::DealDamage(AActor* actor, AActor* FromActor, float damage)
{
	if (!IsValid(actor))
		return;
	if (actor->GetClass()->ImplementsInterface(UDamageableActor::StaticClass())) {
		IDamageableActor::Execute_TakeDamage(actor, FromActor, damage);
	}
}

bool UJT_UtilityFunctions::SpawnProjectile(AActor* Caller, TSubclassOf<AActor> ProjectileClass, FVector RelativeLocation)
{
	if(!IsValid(Caller)
		|| !IsValid(Caller->GetWorld()))
	{
		return false;
	}

	FVector SpawnLocation;
	if(RelativeLocation.IsZero())
	{
		SpawnLocation = Caller->GetActorLocation() + 100 * Caller->GetActorForwardVector();
	}
	else
	{
		SpawnLocation = Caller->GetActorLocation() + RelativeLocation;
	}
	FRotator SpawnRotation = Caller->GetActorRotation();
	
	return IsValid(Caller->GetWorld()->SpawnActor(ProjectileClass.Get(), &SpawnLocation, &SpawnRotation));
}
