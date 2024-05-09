// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DamageableActor.h"
#include "JT_Enemy.generated.h"

class UCapsuleComponent;

UCLASS()
class JAMTEST1_API AJT_Enemy : public APawn, public DamageableActor
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AJT_Enemy();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void TargetPlayer(AActor* Player);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCapsuleComponent* MainCollision;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void TakeDamage_Implementation(float Damage) override;
};
