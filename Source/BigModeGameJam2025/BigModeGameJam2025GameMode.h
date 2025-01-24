// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "BigModeGameJam2025Character.h"
#include "BigModeGameJam2025GameMode.generated.h"

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
private:
	void EndGame(bool bIsPlayerWinner);

	void UpdateStatClamped(float& CurrentStat, float NewValue, float MaxValue);
};



