// Fill out your copyright notice in the Description page of Project Settings.


#include "JT_SkillComponent.h"

// Sets default values for this component's properties
UJT_SkillComponent::UJT_SkillComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UJT_SkillComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if(IsValid(GetWorld()))
	{
		GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
	}
	
	Super::EndPlay(EndPlayReason);
}

bool UJT_SkillComponent::CommitCooldownCost(UInputAction* Skill)
{
	if(SkillsOnCD.Contains(Skill))
	{
		return false;
	}

	StartSkillCD(Skill);
	return true;
}


// Called when the game starts
void UJT_SkillComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UJT_SkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UJT_SkillComponent::StartSkillCD(UInputAction* Skill)
{
	if(!SkillCD_Duration.Contains(Skill))
	{
		return;
	}
	
	if(!IsValid(GetWorld()))
	{
		return;
	}

	SkillsOnCD.AddUnique(Skill);
	
	FTimerHandle Handle;
	FTimerDelegate Delegate;
	Delegate.BindUObject(this,&UJT_SkillComponent::ClearSkillCD, Skill);
	GetWorld()->GetTimerManager().SetTimer(Handle, Delegate, SkillCD_Duration[Skill], false);
}

void UJT_SkillComponent::ClearSkillCD(UInputAction* Skill)
{
	SkillsOnCD.Remove(Skill);
}

