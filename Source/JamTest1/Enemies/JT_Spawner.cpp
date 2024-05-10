// Fill out your copyright notice in the Description page of Project Settings.


#include "JT_Spawner.h"

#include "JT_Enemy.h"
#include "JT_SpawnPhase_DA.h"
#include "JamTest1/JT_GameState.h"

// Sets default values
AJT_Spawner::AJT_Spawner()
{
	CurrentPhaseIndex = -1;
}

void AJT_Spawner::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	ClearTimers();
	
	Super::EndPlay(EndPlayReason);
}

void AJT_Spawner::RestartSequence()
{
	ClearTimers();
	
	CurrentPhaseIndex = -1;
	StartNextPhase();
}

void AJT_Spawner::BeginPlay()
{
	Super::BeginPlay();

	RegisterInGameState();
	RestartSequence();
}

void AJT_Spawner::StartNextPhase()
{
	if (SpawnerPhases.IsEmpty())
	{
		return;
	}

	CurrentPhaseIndex++;
	if (!SpawnerPhases.IsValidIndex(CurrentPhaseIndex))
	{
		UnregisterFromGameState();
		return;
	}

	FJT_SpawnerPhase CurrentPhase = SpawnerPhases[CurrentPhaseIndex];
	ExecutePhase(CurrentPhase);

	if (CurrentPhase.PhaseDuration <= 0.f)
	{
		return;
	}

	if (!IsValid(GetWorld()))
	{
		return;
	}
	FTimerHandle Handle;
	FTimerDelegate Delegate;
	Delegate.BindUObject(this, &AJT_Spawner::OnPhaseEnded, CurrentPhase);
	GetWorld()->GetTimerManager().SetTimer(Handle, Delegate, CurrentPhase.PhaseDuration, false);
}

void AJT_Spawner::SpawnEnemy_Implementation(UClass* EnemyClass, float SpawnRadius)
{
}

void AJT_Spawner::OnPhaseEnded_Implementation(FJT_SpawnerPhase Phase)
{
	if(!Phase.MoveOnPhaseEnded)
	{
		StartNextPhase();
	}
}

void AJT_Spawner::ExecutePhase_Implementation(FJT_SpawnerPhase& Phase)
{
	if(!IsValid(Phase.EnemiesDA))
	{
		return;
	}
	
	float CurrentSpawnRadius;
	if(Phase.SpawnRadiusOverride > 0.f)
	{
		CurrentSpawnRadius = Phase.SpawnRadiusOverride;
	}
	else
	{
		CurrentSpawnRadius = DefaultSpawnRadius;
	}

	TArray<TSubclassOf<AJT_Enemy>> EnemiesClasses;
	Phase.EnemiesDA->EnemiesToSpawn.GetKeys(EnemiesClasses);
	for(TSubclassOf<AJT_Enemy> ClassToSpawn: EnemiesClasses)
	{
		for (int32 i = 0; i < Phase.EnemiesDA->EnemiesToSpawn[ClassToSpawn]; i++)
		{
			SpawnEnemy(ClassToSpawn.Get(), CurrentSpawnRadius);
		}
	}
}

FVector AJT_Spawner::RandomVectorInRange(float Range)
{
	if(Range <= 0.f)
	{
		return FVector();
	}

	FVector2D VectorInCircle = FMath::RandPointInCircle(Range);
	return FVector(VectorInCircle.X, VectorInCircle.Y, 0);
}

void AJT_Spawner::ClearTimers()
{
	if(!IsValid(GetWorld()))
	{
		return;
	}

	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}

void AJT_Spawner::RegisterInGameState()
{
	if(!IsValid(GetWorld()))
	{
		return;
	}

	auto GameState = GetWorld()->GetGameState<AJT_GameState>();
	if(!IsValid(GameState))
	{
		return;
	}

	GameState->RegisterSpawner();
}

void AJT_Spawner::UnregisterFromGameState()
{
	if(!IsValid(GetWorld()))
	{
		return;
	}

	auto GameState = GetWorld()->GetGameState<AJT_GameState>();
	if(!IsValid(GameState))
	{
		return;
	}

	GameState->UnregisterSpawner();
}
