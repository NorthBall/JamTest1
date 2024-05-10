// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.h"
#include "FirstAidKit.generated.h"

UCLASS()
class JAMTEST1_API AFirstAidKit : public APickup
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFirstAidKit();

	void OnEnterPickupBox(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UPROPERTY(EditAnywhere)
	float HealAmount = 50;
};
