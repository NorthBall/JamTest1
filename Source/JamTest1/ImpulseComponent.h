// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ImpulseComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class JAMTEST1_API UImpulseComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UImpulseComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	AActor* Actor;
	float RemainingImpulseTime = 0;
	FVector ImpulseDirection;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void AddImpulse(AActor* FromActor, float Damage);

	void SetActor(AActor* OwnerActor);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Impulse")
	float ImpulseTime = .5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Impulse")
	float ImpulseStrength;
};
