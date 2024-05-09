// Fill out your copyright notice in the Description page of Project Settings.

#include "Pickup.h"
#include "DamageableActor.h"
#include "Components/BoxComponent.h"

// Sets default values
APickup::APickup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PickupBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	PickupBox->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnEnterPickupBox);
	PickupBox->SetGenerateOverlapEvents(true);
	RootComponent = PickupBox;

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	PickupMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void APickup::OnEnterPickupBox(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsValid(Other))
		return;
	if (Other->GetClass()->ImplementsInterface(UDamageableActor::StaticClass())) {
		IDamageableActor::Execute_Heal(Other, HealAmount);
	}
	Destroy();
}