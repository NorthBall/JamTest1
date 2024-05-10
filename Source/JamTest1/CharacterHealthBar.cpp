// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterHealthBar.h"

void UCharacterHealthBar::OnSetHealth(float Value)
{
	if (IsValid(HealthBar)) {
		HealthBar->SetPercent(Value);
	}
}