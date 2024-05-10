// Fill out your copyright notice in the Description page of Project Settings.


#include "ImpulseComponent.h"

// Sets default values for this component's properties
UImpulseComponent::UImpulseComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UImpulseComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UImpulseComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsValid(Actor)) {
		if (RemainingImpulseTime > 0) {
			FVector Target = Actor->GetActorLocation() - ImpulseDirection;
			FVector NewLoc = FMath::VInterpConstantTo(Actor->GetActorLocation(), Target, DeltaTime, ImpulseStrength);
			Actor->SetActorLocation(NewLoc, true);
			RemainingImpulseTime -= DeltaTime;
		}
	}
}

void UImpulseComponent::AddImpulse(AActor* FromActor, float Impulse)
{
	if (IsValid(FromActor) && IsValid(Actor)) {
		RemainingImpulseTime = ImpulseTime;
		ImpulseDirection = (FromActor->GetActorLocation() - Actor->GetActorLocation()) * 1000;
		ImpulseDirection.Z = 0;
		ImpulseStrength = Impulse;
	}
}

void UImpulseComponent::SetActor(AActor* OwnerActor)
{
	Actor = OwnerActor;
}
