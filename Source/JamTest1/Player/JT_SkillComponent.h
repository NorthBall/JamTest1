// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "JT_SkillComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEffectAddedSignature, FGameplayTag, EffectTag, FTimerHandle, Timer);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEffectUpdatedSignature, FGameplayTag, EffectTag, FTimerHandle, NewTimer);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEffectRemovedSignature, FGameplayTag, EffectTag);

class UInputAction;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class JAMTEST1_API UJT_SkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UJT_SkillComponent();

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(BlueprintAssignable)
	FOnEffectAddedSignature OnEffectAdded;
	UPROPERTY(BlueprintAssignable)
	FOnEffectUpdatedSignature OnEffectUpdated;
	UPROPERTY(BlueprintAssignable)
	FOnEffectRemovedSignature OnEffectRemoved;
	UFUNCTION(BlueprintCallable)
	bool CommitCooldownCost(UInputAction* Skill);
	UFUNCTION(BlueprintCallable)
	bool ApplyEffect(FGameplayTag EffectTag, float Duration);
	UFUNCTION(BlueprintCallable)
	bool HasEffect(FGameplayTag EffectTag);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<UInputAction*, float> SkillCD_Duration;
	UPROPERTY()
	TArray<UInputAction*> SkillsOnCD;

	UPROPERTY()
	TMap<FGameplayTag, FTimerHandle> ActiveEffects;

private:
	UFUNCTION()
	void StartSkillCD(UInputAction* Skill);
	UFUNCTION()
	void ClearSkillCD(UInputAction* Skill);

	UFUNCTION()
	void OnEffectEnded(FGameplayTag EffectTag);
};
