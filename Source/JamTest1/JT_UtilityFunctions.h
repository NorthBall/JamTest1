// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DamageableActor.h"
#include "DamageComponent.h"
#include "JT_UtilityFunctions.generated.h"

UCLASS()
class JAMTEST1_API UJT_UtilityFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "DealDamage")
	static void DealDamage(AActor* Actor, AActor* FromActor, float Damage);

	UFUNCTION(BlueprintCallable, Category = "DealDamage")
	static UDamageComponent* GetDamageComponent(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category = "DealDamage")
	static void AddImpulse(AActor* Actor, AActor* FromActor, float Impulse);

	UFUNCTION(BlueprintCallable)
	static bool SpawnProjectile(AActor* Caller, TSubclassOf<AActor> ProjectileClass, FVector RelativeLocation = FVector(0,0,0));
};
