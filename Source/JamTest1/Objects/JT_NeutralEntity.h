// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JamTest1/DamageableActor.h"
#include "JT_NeutralEntity.generated.h"

class UWidgetComponent;
class UWidgetComponent;

UCLASS()
class JAMTEST1_API AJT_NeutralEntity : public AActor, public IDamageableActor
{
	GENERATED_BODY()

public:
	AJT_NeutralEntity();

	virtual UDamageComponent* GetDamageComponent_Implementation() override;
	virtual void TakeDamage_Implementation(AActor* From, float Damage) override;
	virtual void AddImpulse_Implementation(AActor* From, float Impulse) override;

	UPROPERTY(VisibleAnywhere)
	UDamageComponent* DamageComponent;

	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* HealthBarWidget;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	bool bIsKeyPoint;
	
	UFUNCTION(BlueprintNativeEvent)
	void OnDeath();
	
private:
	UFUNCTION()
	void RegisterInGameState();
	UFUNCTION()
	void UnregisterFromGameState();

	UPROPERTY()
	bool bRegisteredInGameState;
};