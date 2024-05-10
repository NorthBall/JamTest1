// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "JT_SkillComponent.generated.h"


class UInputAction;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class JAMTEST1_API UJT_SkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UJT_SkillComponent();

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(BlueprintCallable)
	bool CommitCooldownCost(UInputAction* Skill);
	UFUNCTION(BlueprintCallable)
	bool ApplyEffect(FGameplayTag EffectTag, float Duration);

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
