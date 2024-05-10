// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterHealthBar.h"
#include "Delegates/Delegate.h"
#include "DamageComponent.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnSetHealthDelegate, float, Value);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class JAMTEST1_API UDamageComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDamageComponent();

	void SetHealthBarWidget(UCharacterHealthBar* healthBar) { HealthBar = healthBar; }

	UFUNCTION()
	void TakeDamage(float Damage);

	UFUNCTION(BlueprintCallable)
	float GetHealthPercent();

	UFUNCTION()
	bool IsDead();

	UFUNCTION()
	void Heal(float Heal);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth;
	UPROPERTY(BlueprintReadOnly)
	float CurrentHealth;

	FOnSetHealthDelegate OnSetHealthDelegate;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UCharacterHealthBar* HealthBar;
};
