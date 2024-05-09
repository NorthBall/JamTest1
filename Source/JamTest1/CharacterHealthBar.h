// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "DamageableActor.h"
#include "CharacterHealthBar.generated.h"

/**
 * 
 */
UCLASS( Abstract )
class JAMTEST1_API UCharacterHealthBar : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetHealthBarValue(float value);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* HealthBar;
};