// Fill out your copyright notice in the Description page of Project Settings.


#include "JT_UtilityFunctions.h"

void UJT_UtilityFunctions::DealDamage(AActor* Actor, AActor* FromActor, float Damage)
{
	if (!IsValid(Actor))
		return;
	if (Actor->GetClass()->ImplementsInterface(UDamageableActor::StaticClass())) {
		IDamageableActor::Execute_TakeDamage(Actor, FromActor, Damage);
	}
}

void UJT_UtilityFunctions::AddImpulse(AActor* Actor, AActor* FromActor, float Impulse)
{
	if (!IsValid(Actor))
		return;
	if (Actor->GetClass()->ImplementsInterface(UDamageableActor::StaticClass())) {
		IDamageableActor::Execute_AddImpulse(Actor, FromActor, Impulse);
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
