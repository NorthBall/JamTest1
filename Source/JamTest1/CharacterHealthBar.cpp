// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterHealthBar.h"

void UCharacterHealthBar::SetHealthBarValue(float Value)
{
	HealthBar->SetPercent(Value);
}