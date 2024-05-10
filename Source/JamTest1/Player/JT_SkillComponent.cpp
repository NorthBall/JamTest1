// Fill out your copyright notice in the Description page of Project Settings.


#include "JT_SkillComponent.h"

#include "JamTest1/JamTest1Character.h"

UJT_SkillComponent::UJT_SkillComponent()
{
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

bool UJT_SkillComponent::ApplyEffect(FGameplayTag EffectTag, float Duration)
{	
	if(!IsValid(GetWorld()))
	{
		return false;
	}

	FTimerHandle Handle;

	//Has this effect
	if(ActiveEffects.Contains(EffectTag))
	{
		Handle = ActiveEffects[EffectTag];
		//Existing effect duration cannot be increased
		if (GetWorld()->GetTimerManager().GetTimerRemaining(Handle) >= Duration)
		{
			return false;
		}
	}
	
	FTimerDelegate Delegate;
	Delegate.BindUObject(this,&UJT_SkillComponent::OnEffectEnded, EffectTag);
	GetWorld()->GetTimerManager().SetTimer(Handle, Delegate, Duration, false);

	return true;
}

void UJT_SkillComponent::BeginPlay()
{
	Super::BeginPlay();
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

void UJT_SkillComponent::OnEffectEnded(FGameplayTag EffectTag)
{
	if(!EffectTag.MatchesTag(FGameplayTag::RequestGameplayTag("Effect.Weapon")))
	{
		return;
	}

	auto PlayerChar = Cast<AJamTest1Character>(GetOwner());
	if(!IsValid(PlayerChar))
	{
		return;
	}

	PlayerChar->RemoveWeapon(EffectTag);
}

