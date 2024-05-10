// Fill out your copyright notice in the Description page of Project Settings.


#include "JT_UtilityFunctions.h"
#include "JamTest1Character.h"
#include "Player/JT_SkillComponent.h"

void UJT_UtilityFunctions::DealDamage(AActor* Actor, AActor* FromActor, float Damage)
{
	if (!IsValid(Actor))
		return;
	if (Actor->GetClass()->ImplementsInterface(UDamageableActor::StaticClass())) {
		auto PlayerChar = Cast<AJamTest1Character>(FromActor);
		if (!IsValid(PlayerChar) && PlayerChar->SkillComponent->HasEffect(FGameplayTag::RequestGameplayTag("Effect.DoubleDamage"))) {
			Damage *= 2;
		}
		IDamageableActor::Execute_TakeDamage(Actor, FromActor, Damage);
	}
}

UDamageComponent* UJT_UtilityFunctions::GetDamageComponent(AActor* Actor)
{
	if (IsValid(Actor) && Actor->GetClass()->ImplementsInterface(UDamageableActor::StaticClass())) {
		return IDamageableActor::Execute_GetDamageComponent(Actor);
	}
	return nullptr;
}

void UJT_UtilityFunctions::AddImpulse(AActor* Actor, AActor* FromActor, float Impulse)
{
	if (!IsValid(Actor))
		return;
	if (Actor->GetClass()->ImplementsInterface(UDamageableActor::StaticClass())) {
		IDamageableActor::Execute_AddImpulse(Actor, FromActor, Impulse);
	}
}

bool UJT_UtilityFunctions::ApplyEffect(AActor* Actor, FGameplayTag EffectTag, float Duration)
{
	auto PlayerChar = Cast<AJamTest1Character>(Actor);
	if(!IsValid(PlayerChar))
	{
		return false;
	}

	return PlayerChar->SkillComponent->ApplyEffect(EffectTag, Duration);
}

bool UJT_UtilityFunctions::HasEffect(AActor* Actor, FGameplayTag EffectTag)
{
	auto PlayerChar = Cast<AJamTest1Character>(Actor);
	if(!IsValid(PlayerChar))
	{
		return false;
	}

	return PlayerChar->SkillComponent->HasEffect(EffectTag);
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
