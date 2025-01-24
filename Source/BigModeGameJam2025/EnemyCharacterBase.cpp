// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacterBase.h"
#include "BigModeGameJam2025GameMode.h"

// Sets default values
AEnemyCharacterBase::AEnemyCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

float AEnemyCharacterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DammageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DammageToApply = FMath::Min(CurrentHealth, DammageToApply);
	CurrentHealth-= DammageToApply;
	UE_LOG(LogTemp, Warning, TEXT("Dammaged %f"), CurrentHealth);

	//If the character is dead, notify the game mode and destroy the character
	if (IsDead()) {
		ABigModeGameJam2025GameMode* GameMode = GetWorld()->GetAuthGameMode<ABigModeGameJam2025GameMode>();
		if (GameMode != nullptr) {
			GameMode->PawnKilled(this);
		}

		DetachFromControllerPendingDestroy();
		//GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	return DammageToApply;
}

bool AEnemyCharacterBase::IsDead() const
{
	return CurrentHealth <= 0;
}

// Called when the game starts or when spawned
void AEnemyCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

