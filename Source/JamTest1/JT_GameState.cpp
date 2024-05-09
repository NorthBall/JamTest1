// Fill out your copyright notice in the Description page of Project Settings.


#include "JT_GameState.h"

#include "EngineUtils.h"
#include "JamTest1GameMode.h"
#include "Enemies/JT_Enemy.h"

void AJT_GameState::ResetEnemies(int32 NewValue)
{
	RemainingEnemies = NewValue;
}

void AJT_GameState::AddEnemy()
{
	RemainingEnemies++;
}

void AJT_GameState::RemoveEnemy()
{
	RemainingEnemies--;
	if (RemainingEnemies <= 0)
	{
		OnLevelCleared();
	}
}

bool AJT_GameState::OnLevelCleared_Implementation()
{
	if (!IsValid(GetWorld()))
	{
		return false;
	}

	int32 NumOfAliveEnemies = 0;
	for (TActorIterator<AJT_Enemy> It(GetWorld()); It; ++It)
	{
		if (IsValid(*It))
		{
			NumOfAliveEnemies++;
		}
	}

	//Last Enemy will be alive, when calling this method
	if(NumOfAliveEnemies >= 2)
	{
		return false;
	}
	
	auto GameMode = GetWorld()->GetAuthGameMode<AJamTest1GameMode>();
	if (IsValid(GameMode))
	{
		GameMode->PlayerWin();
	}

	return true;
}
