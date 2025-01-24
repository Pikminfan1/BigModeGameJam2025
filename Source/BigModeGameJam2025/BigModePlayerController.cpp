// Fill out your copyright notice in the Description page of Project Settings.


#include "BigModePlayerController.h"
#include "Blueprint/UserWidget.h"


void ABigModePlayerController::BeginPlay()
{
	Super::BeginPlay();
	PlayerHUDInstance = CreateWidget(this, PlayerHUDClass);
	if (PlayerHUDInstance != nullptr) {
		PlayerHUDInstance->AddToViewport();
	}else { UE_LOG(LogTemp, Error, TEXT("Failed to create the widget instance.")); }
}
