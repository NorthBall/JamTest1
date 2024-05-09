// Fill out your copyright notice in the Description page of Project Settings.


#include "JT_GameState.h"

#include "EngineUtils.h"
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
	if(RemainingEnemies <= 0)
	{
		OnLevelCleared();
	}
}

bool AJT_GameState::OnLevelCleared_Implementation()
{
	if(!IsValid(GetWorld()))
	{
		return false;
	}

	for (TActorIterator<AJT_Enemy> It(GetWorld()); It; ++It)
	{
		return false;
	}
	
	return true;
}
