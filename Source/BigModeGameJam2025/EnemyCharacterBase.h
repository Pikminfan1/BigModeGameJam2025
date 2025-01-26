// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacterBase.generated.h"

UCLASS()
class BIGMODEGAMEJAM2025_API AEnemyCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:

	/** The range of the melee attack */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float MeleeRange = 150.0f;
	// Sets default values for this character's properties
	AEnemyCharacterBase();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

	virtual void MeleeAttack();

	bool IsDead() const;

private:
	/** Variables Used to Hold Stat changes**/
	UPROPERTY(EditAnywhere, Category = Stats)
	float CurrentHealth = 100.0f;

	UPROPERTY(EditAnywhere, Category = Stats)
	float MaxHealth = 100.0f;

	UPROPERTY(EditAnywhere, Category = Stats)
	float CurrentSpeed = 100.0f;

	UPROPERTY(EditAnywhere, Category = Stats)
	float MaxSpeed = 100.0f;

	UPROPERTY(EditAnywhere, Category = Stats)
	float CurrentJumpVelocity = 100.0f;

	UPROPERTY(EditAnywhere, Category = Stats)
	float MaxJumpVelocity = 100.0f;

	UPROPERTY(EditAnywhere, Category = Leveling)
	float BaseExperienceReward = 100.0f;

	UPROPERTY(EditAnywhere, Category = Leveling)
	float ExperienceMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, Category = Combat)
	TObjectPtr<UAnimMontage> MeleeAttackMontage;

protected:

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Timer handle to re-enable movement after melee attack */
	FTimerHandle MeleeAttackTimerHandle;

	/** Timer handle to perform hit detection during melee attack */
	FTimerHandle HitCheckTimerHandle;



	/** The radius of the melee attack (for sphere sweep) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float MeleeRadius = 50.0f;

	/** The damage value of the melee attack */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float MeleeDamage = 20.0f;

	/** The delay before hit detection is performed during an attack (seconds) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float HitDelay = 0.5f;

public:	

	void EnableMovement();

	void PerformMeleeHitCheck();

	virtual float GetExperienceReward() const;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
