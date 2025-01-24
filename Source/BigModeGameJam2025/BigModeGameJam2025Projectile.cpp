// Copyright Epic Games, Inc. All Rights Reserved.

#include "BigModeGameJam2025Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "BigModeGameJam2025GameMode.h"

ABigModeGameJam2025Projectile::ABigModeGameJam2025Projectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &ABigModeGameJam2025Projectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void ABigModeGameJam2025Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if (OtherComp->IsSimulatingPhysics()) {

			OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		}
		Destroy();

		//Cause Dammage to the hit actor if enemy
		if(OtherActor->ActorHasTag("Enemy"))
		{
			FHitResult Hit;
			FVector ShotDirection;
			FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			ABigModeGameJam2025GameMode* GameMode = Cast<ABigModeGameJam2025GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
			UE_LOG(LogTemp, Warning, TEXT("Hit an enemy!"));
			OtherActor->TakeDamage(GameMode->GetCurrentDamage(), DamageEvent, PlayerController, this);
		}

	}
}