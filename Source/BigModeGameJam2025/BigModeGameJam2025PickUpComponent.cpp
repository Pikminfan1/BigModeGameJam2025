// Copyright Epic Games, Inc. All Rights Reserved.

#include "BigModeGameJam2025PickUpComponent.h"

UBigModeGameJam2025PickUpComponent::UBigModeGameJam2025PickUpComponent()
{
	// Setup the Sphere Collision
	SphereRadius = 32.f;
}

void UBigModeGameJam2025PickUpComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register our Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &UBigModeGameJam2025PickUpComponent::OnSphereBeginOverlap);
}

void UBigModeGameJam2025PickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Checking if it is a First Person Character overlapping
	ABigModeGameJam2025Character* Character = Cast<ABigModeGameJam2025Character>(OtherActor);
	if(Character != nullptr)
	{
		// Notify that the actor is being picked up
		OnPickUp.Broadcast(Character);

		// Unregister from the Overlap Event so it is no longer triggered
		OnComponentBeginOverlap.RemoveAll(this);
	}
}
