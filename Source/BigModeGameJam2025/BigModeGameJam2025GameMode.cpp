// Copyright Epic Games, Inc. All Rights Reserved.

#include "BigModeGameJam2025GameMode.h"
#include "BigModeGameJam2025Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UObject/ConstructorHelpers.h"

#include "EnemyCharacterBase.h"

void ABigModeGameJam2025GameMode::BeginPlay()
{
		Super::BeginPlay();
		Player = Cast<ABigModeGameJam2025Character>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

ABigModeGameJam2025GameMode::ABigModeGameJam2025GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;


	
	

}

void ABigModeGameJam2025GameMode::PawnKilled(APawn* PawnKilled)
{
	//CHANGE THIS
	if(PawnKilled == nullptr) return;

	if(PawnKilled == GetWorld()->GetFirstPlayerController()->GetPawn())
	{
		EndGame(false);
	}

	if(PawnKilled->IsA(AEnemyCharacterBase::StaticClass()))
	{

		if (PawnKilled->ActorHasTag("SpeedType"))
		{
			SetCurrentSpeed(GetCurrentSpeed() + 500.0f);
		}
		if (PawnKilled->ActorHasTag("DamageType"))
		{
			SetCurrentDamage(GetCurrentDamage() + 10.0f);
		}
		if (PawnKilled->ActorHasTag("JumpType"))
		{
			//Player->UpdateMaxSpeed(GetCurrentSpeed() + 100.0f);
			//Player->GetCharacterMovement()->JumpZVelocity = 500.0f;;
			SetCurrentJumpVelocity(GetCurrentJumpVelocity() + 500.0f);
		}
		PawnKilled->Destroy();
		//EndGame(true);
	}
}

void ABigModeGameJam2025GameMode::EndGame(bool bIsPlayerWinner)
{
}

void ABigModeGameJam2025GameMode::SetCurrentHealth(float NewHealth)
{
	UpdateStatClamped(CurrentHealth, NewHealth, MaxHealth);
}

void ABigModeGameJam2025GameMode::SetCurrentSpeed(float NewSpeed)
{
	UpdateStatClamped(Player->GetCharacterMovement()->MaxWalkSpeed, NewSpeed, MaxSpeed);
}

void ABigModeGameJam2025GameMode::SetCurrentJumpVelocity(float NewJumpVelocity)
{
	if (Player == nullptr || Player->GetCharacterMovement() == nullptr) return;
	UpdateStatClamped(Player->GetCharacterMovement()->JumpZVelocity, NewJumpVelocity, MaxJumpVelocity);
}

void ABigModeGameJam2025GameMode::SetCurrentDamage(float NewDamage)
{
	UpdateStatClamped(CurrentDamage, NewDamage, MaxDamage);
}

float ABigModeGameJam2025GameMode::GetCurrentHealth()
{
	
	//Player->GetCharacterMovement()->
	return CurrentHealth;
}

float ABigModeGameJam2025GameMode::GetCurrentSpeed()
{
	if (Player == nullptr || Player->GetCharacterMovement() == nullptr) return 0.0f;
	return Player->GetCharacterMovement()->MaxWalkSpeed;
}

float ABigModeGameJam2025GameMode::GetCurrentJumpVelocity()
{
	if(Player == nullptr || Player->GetCharacterMovement() == nullptr) return 0.0f;
	return Player->GetCharacterMovement()->JumpZVelocity;
}

float ABigModeGameJam2025GameMode::GetCurrentDamage()
{
	return CurrentDamage;
}

void ABigModeGameJam2025GameMode::UpdateStatClamped(float& CurrentStat, float NewValue, float MaxValue) {
		CurrentStat = FMath::Clamp(NewValue, 0.0f, MaxValue);
}