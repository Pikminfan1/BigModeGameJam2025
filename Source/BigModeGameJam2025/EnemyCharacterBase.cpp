// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacterBase.h"
#include "BigModeGameJam2025GameMode.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimMontage.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AEnemyCharacterBase::AEnemyCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

/*Temp Remove for damage blueprint component system
float AEnemyCharacterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	//Maybe move this, but for now it's fine
	DamageToApply *= GetWorld()->GetAuthGameMode<ABigModeGameJam2025GameMode>()->GetCurrentDamageLevel();

	DamageToApply = FMath::Min(CurrentHealth, DamageToApply);
	CurrentHealth-= DamageToApply;
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
	return DamageToApply;
}*/

void AEnemyCharacterBase::MeleeAttack()
{
	if (!MeleeAttackMontage) return;

	GetCharacterMovement()->DisableMovement();

	PlayAnimMontage(MeleeAttackMontage);

	// Setup a timer to re-enable movement after animation
	const float AnimationDuration = MeleeAttackMontage->GetPlayLength();
	GetWorld()->GetTimerManager().SetTimer(MeleeAttackTimerHandle, this, &AEnemyCharacterBase::EnableMovement, AnimationDuration, false);

	// Trigger hit logic at the right time
	//GetWorld()->GetTimerManager().SetTimer(HitCheckTimerHandle, this, &AEnemyCharacterBase::PerformMeleeHitCheck, HitDelay, false);
}
/*
bool AEnemyCharacterBase::IsDead() const
{
	//return CurrentHealth <= 0;
}*/

// Called when the game starts or when spawned
void AEnemyCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemyCharacterBase::EnableMovement()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

float AEnemyCharacterBase::GetExperienceReward() const
{
	return BaseExperienceReward * ExperienceMultiplier;
}

void AEnemyCharacterBase::PerformMeleeHitCheck()
{
	// Perform a sphere trace to detect enemies in range
	TArray<FHitResult> OutHits;
	const FVector TraceStart = GetActorLocation();
	const FVector TraceEnd = TraceStart + GetActorForwardVector() * MeleeRange;
	const FQuat Rotation = FQuat(GetActorRotation());
	const FCollisionShape CollisionShape = FCollisionShape::MakeSphere(MeleeRadius);
	const FCollisionQueryParams CollisionParams;
	const bool bHit = GetWorld()->SweepMultiByChannel(OutHits, TraceStart, TraceEnd, Rotation, ECC_Pawn, CollisionShape, CollisionParams);

	// Check if any enemies were hit
	for (const FHitResult& Hit : OutHits)
	{
		ACharacter* HitCharacter = Cast<ACharacter>(Hit.GetActor());
		if (HitCharacter && HitCharacter != this)
		{
			// Apply damage to the hit character
			UGameplayStatics::ApplyDamage(HitCharacter, MeleeDamage, GetController(), this, UDamageType::StaticClass());
		}
	}
}

// Called every frame
void AEnemyCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
//Moved to blueprint damage component
/*
float AEnemyCharacterBase::GetMaxHealth() const
{
	return MaxHealth;
}*/

// Called to bind functionality to input
void AEnemyCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AEnemyCharacterBase::GetMaxJumpVelocity() const
{
	return MaxJumpVelocity;
}

float AEnemyCharacterBase::GetBaseExperienceReward() const
{
	return BaseExperienceReward;
}

float AEnemyCharacterBase::GetExperienceMultiplier() const
{
	return ExperienceMultiplier;
}
/*
* Moved to Blueprint Damage Component
float AEnemyCharacterBase::GetCurrentHealth() const
{
	return CurrentHealth;
}

void AEnemyCharacterBase::SetEnemyCurrentHealth(float NewHealth)
{
	CurrentHealth = NewHealth;
}

void AEnemyCharacterBase::SetEnemyMaxHealth(float NewMaxHealth)
{
		MaxHealth = NewMaxHealth;
}*/

float AEnemyCharacterBase::GetMaxSpeed() const
{
	return MaxSpeed;
}

