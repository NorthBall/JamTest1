// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "JamTest1GameMode.generated.h"

UCLASS(minimalapi)
class AJamTest1GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AJamTest1GameMode();

protected:
	virtual void BeginPlay() override;
};



