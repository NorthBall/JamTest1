// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstAidKit.h"
#include "JamTest1Character.h"
#include "DamageableActor.h"

// Sets default values
AFirstAidKit::AFirstAidKit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AFirstAidKit::OnEnterPickupBox_Implementation(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(Cast<AJamTest1Character>(Other))) {
		IDamageableActor::Execute_Heal(Other, HealAmount);
		Destroy();
	}
}
