// Fill out your copyright notice in the Description page of Project Settings.


#include "JT_UtilityFunctions.h"

void UJT_UtilityFunctions::DealDamage(AActor* actor, float damage)
{
	if (!IsValid(actor))
		return;
	if (actor->GetClass()->ImplementsInterface(UDamageableActor::StaticClass())) {
		IDamageableActor::Execute_TakeDamage(actor, damage);
	}
}