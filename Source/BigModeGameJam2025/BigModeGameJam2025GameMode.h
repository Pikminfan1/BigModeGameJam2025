// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "BigModeGameJam2025Character.h"
#include "BigModeGameJam2025GameMode.generated.h"


//Defined Constants

#define BASE_HEALTH_REWARD  50.0f;
#define BASE_SPEED_REWARD 50.0f;
#define BASE_JUMP_VELOCITY_REWARD 50.0f;
#define BASE_DAMAGE_REWARD 10.0f;

#define BASE_HEALTH 100.0f;
#define BASE_SPEED 420.0f;
#define BASE_JUMP_VELOCITY 100.0f;
#define BASE_DAMAGE 5.0f;

UCLASS(minimalapi)
class ABigModeGameJam2025GameMode : public AGameModeBase
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
public:
	ABigModeGameJam2025GameMode();

	ABigModeGameJam2025Character* Player;

	virtual void PawnKilled(APawn* PawnKilled);

private:
	//Variables for Game Logic
	UPROPERTY(EditAnywhere, Category = GameLogic)
	int32 EnemyCount = 0;

	/** Variables Used to Hold Stat changes**/

	UPROPERTY(EditAnywhere, Category = Stats)
	float CurrentHealth = 100.0f;

	UPROPERTY(EditAnywhere, Category = Stats)
	float MaxHealth = 100.0f;

	UPROPERTY(EditAnywhere, Category = Stats)
	float CurrentSpeed = 420.0;

	UPROPERTY(EditAnywhere, Category = Stats)
	float MaxSpeed = 5000.0f;

	UPROPERTY(EditAnywhere, Category = Stats)
	float CurrentJumpVelocity = 100.0f;

	UPROPERTY(EditAnywhere, Category = Stats)
	float MaxJumpVelocity = 5000.0f;

	UPROPERTY(EditAnywhere, Category = Stats)
	float CurrentDamage = 10.0f;

	UPROPERTY(EditAnywhere, Category = Stats)
	float MaxDamage = 100.0f;

	//Variables Used for Experience points system
	UPROPERTY(EditAnywhere, Category = Leveling)
	int32 CurrentHealthLevel = 1;

	UPROPERTY(EditAnywhere, Category = Leveling)
	float CurrentHealthExperience = 0.0f;

	UPROPERTY(EditAnywhere, Category = Leveling)
	float BaseHealthExperienceThreshold = 100.0f;

	UPROPERTY(EditAnywhere, Category = Leveling)
	float HealthExperienceMultiplier = 1.5f;

	UPROPERTY(EditAnywhere, Category = Leveling)
	int32 CurrentSpeedLevel = 1;

	UPROPERTY(EditAnywhere, Category = Leveling)
	float CurrentSpeedExperience = 0.0f;

	UPROPERTY(EditAnywhere, Category = Leveling)
	float BaseSpeedExperienceThreshold = 100.0f;

	UPROPERTY(EditAnywhere, Category = Leveling)
	float SpeedExperienceMultiplier = 1.5f;

	UPROPERTY(EditAnywhere, Category = Leveling)
	int32 CurrentJumpVelocityLevel = 1;

	UPROPERTY(EditAnywhere, Category = Leveling)
	float CurrentJumpVelocityExperience = 0.0f;

	UPROPERTY(EditAnywhere, Category = Leveling)
	float BaseJumpVelocityExperienceThreshold = 100.0f;

	UPROPERTY(EditAnywhere, Category = Leveling)
	float JumpVelocityExperienceMultiplier = 1.5f;

	UPROPERTY(EditAnywhere, Category = Leveling)
	int32 CurrentDamageLevel = 1;

	UPROPERTY(EditAnywhere, Category = Leveling)
	float CurrentDamageExperience = 0.0f;

	UPROPERTY(EditAnywhere, Category = Leveling)
	float BaseDamageExperienceThreshold = 10.f;

	UPROPERTY(EditAnywhere, Category = Leveling)
	float DamageExperienceMultiplier = 1.5f;



public:
	UFUNCTION(BlueprintCallable, Category = "Stats")
	void SetCurrentHealth(float NewHealth);

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void SetCurrentSpeed(float NewSpeed);

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void SetCurrentJumpVelocity(float NewJumpVelocity);

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void SetCurrentDamage(float NewDamage);

	UFUNCTION(BlueprintCallable, Category = "Stats")
	float GetCurrentHealth();

	UFUNCTION(BlueprintCallable, Category = "Stats")
	float GetCurrentSpeed();

	UFUNCTION(BlueprintCallable, Category = "Stats")
	float GetCurrentJumpVelocity();

	UFUNCTION(BlueprintCallable, Category = "Stats")
	float GetCurrentDamage();

	UFUNCTION(BlueprintCallable, Category = "Leveling")
	void AddHealthExperience(float HealthExperience);

	UFUNCTION(BlueprintCallable, Category = "Leveling")
	void AddSpeedExperience(float SpeedExperience);

	UFUNCTION(BlueprintCallable, Category = "Leveling")
	void AddJumpVelocityExperience(float JumpVelocityExperience);

	UFUNCTION(BlueprintCallable, Category = "Leveling")
	void AddDamageExperience(float DamageExperience);

	UFUNCTION(BlueprintCallable, Category = "Leveling")
	void LevelUpHealth();

	UFUNCTION(BlueprintCallable, Category = "Leveling")
	void LevelUpSpeed();

	UFUNCTION(BlueprintCallable, Category = "Leveling")
	void LevelUpJumpVelocity();

	UFUNCTION(BlueprintCallable, Category = "Leveling")
	void LevelUpDamage();

	UFUNCTION(BlueprintCallable, Category = "Leveling")
	int32 GetCurrentHealthLevel();

	UFUNCTION(BlueprintCallable, Category = "Leveling")
	int32 GetCurrentSpeedLevel();

	UFUNCTION(BlueprintCallable, Category = "Leveling")
	int32 GetCurrentJumpVelocityLevel();

	UFUNCTION(BlueprintCallable, Category = "Leveling")
	int32 GetCurrentDamageLevel();

private:
	void EndGame(bool bIsPlayerWinner);

	void UpdateStatClamped(float& CurrentStat, float NewValue, float MaxValue);
};



