// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "JT_SpawnPhase_DA.generated.h"

class AJT_Enemy;

UCLASS()
class JAMTEST1_API UJT_SpawnPhase_DA : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TMap<TSubclassOf<AJT_Enemy>, int32> EnemiesToSpawn;
};
