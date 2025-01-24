// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "BigModePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BIGMODEGAMEJAM2025_API ABigModePlayerController : public APlayerController
{
	GENERATED_BODY()
	

protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> PlayerHUDClass;

	UPROPERTY()
	TObjectPtr<UUserWidget> PlayerHUDInstance;
};
