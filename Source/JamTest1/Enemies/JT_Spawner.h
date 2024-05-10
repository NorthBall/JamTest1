// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JT_Spawner.generated.h"


class UJT_SpawnPhase_DA;

USTRUCT(BlueprintType)
struct FJT_SpawnerPhase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PhaseDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool MoveOnPhaseEnded;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnRadiusOverride;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UJT_SpawnPhase_DA* EnemiesDA;
};

UCLASS()
class JAMTEST1_API AJT_Spawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJT_Spawner();

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()
	void RestartSequence();
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TArray<FJT_SpawnerPhase> SpawnerPhases;
	UPROPERTY(EditAnywhere)
	float DefaultSpawnRadius;

	UFUNCTION(BlueprintCallable)
	void StartNextPhase();
	UFUNCTION(BlueprintNativeEvent)
	void ExecutePhase(FJT_SpawnerPhase& Phase);
	UFUNCTION(BlueprintNativeEvent)
	void SpawnEnemy(UClass* EnemyClass, float SpawnRadius);
	UFUNCTION(BlueprintNativeEvent)
	void OnPhaseEnded(FJT_SpawnerPhase Phase);

	UFUNCTION(BlueprintPure)
	FVector RandomVectorInRange(float Range);
	
private:
	UPROPERTY()
	int32 CurrentPhaseIndex;

	UFUNCTION()
	void ClearTimers();
	UFUNCTION()
	void RegisterInGameState();
	UFUNCTION()
	void UnregisterFromGameState();
};
