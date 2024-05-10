// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "JT_GameState.generated.h"

UCLASS()
class JAMTEST1_API AJT_GameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void ResetEnemies(int32 NewValue);
	UFUNCTION()
	void AddEnemy();
	UFUNCTION()
	void RemoveEnemy();
	UFUNCTION()
	void ResetSpawners(int32 NewValue);
	UFUNCTION()
	void RegisterSpawner();
	UFUNCTION()
	void UnregisterSpawner();
	
protected:
	UPROPERTY(BlueprintReadWrite)
	int32 RemainingEnemies;
	UPROPERTY(BlueprintReadWrite)
	int32 RemainingSpawners;

	UFUNCTION(BlueprintNativeEvent)
	bool OnLevelCleared();
};
