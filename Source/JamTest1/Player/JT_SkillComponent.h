// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

	UFUNCTION(BlueprintCallable)
	bool CommitCooldownCost(UInputAction* Skill);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<UInputAction*, float> SkillCD_Duration;
	UPROPERTY()
	TArray<UInputAction*> SkillsOnCD;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UFUNCTION()
	void StartSkillCD(UInputAction* Skill);
	UFUNCTION()
	void ClearSkillCD(UInputAction* Skill);
};
