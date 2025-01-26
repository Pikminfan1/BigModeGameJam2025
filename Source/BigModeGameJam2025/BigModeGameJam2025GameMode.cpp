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


	// Array to hold all actors of type ACharacter
	TArray<AActor*> FoundCharacters;

	// Get all characters in the level
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACharacter::StaticClass(), FoundCharacters);

	// Iterate through the array and check for the "enemy" tag
	for (AActor* Actor : FoundCharacters)
	{
		if (Actor->ActorHasTag(FName("enemy")))
		{
			UE_LOG(LogTemp, Log, TEXT("Enemy found: %s"), *Actor->GetName());
			EnemyCount++;
		}
	}

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
		//Cast PawnKilled to EnemyCharacterBase
		AEnemyCharacterBase* EnemyKilled = Cast<AEnemyCharacterBase>(PawnKilled);

		//Add experience to the player based on the enemy killed and too each tag type satisfied
		if (PawnKilled->ActorHasTag("SpeedType"))
		{
			
			AddSpeedExperience(EnemyKilled->GetExperienceReward());
		}
		if (PawnKilled->ActorHasTag("DamageType"))
		{
			
			AddDamageExperience(EnemyKilled->GetExperienceReward());
		}
		if (PawnKilled->ActorHasTag("JumpType"))
			{
			
			AddJumpVelocityExperience(EnemyKilled->GetExperienceReward());
		}
		

		EnemyCount--;
		UE_LOG(LogTemp, Log, TEXT("Enemy Count: %d"), EnemyCount);
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

void ABigModeGameJam2025GameMode::AddHealthExperience(float HealthExperience)
{
	CurrentHealthExperience += HealthExperience;
	LevelUpHealth();
}

void ABigModeGameJam2025GameMode::AddSpeedExperience(float SpeedExperience)
{
	CurrentSpeedExperience += SpeedExperience;
	LevelUpSpeed();
}

void ABigModeGameJam2025GameMode::AddJumpVelocityExperience(float JumpVelocityExperience)
{
	CurrentJumpVelocityExperience += JumpVelocityExperience;
	LevelUpJumpVelocity();
}

void ABigModeGameJam2025GameMode::AddDamageExperience(float DamageExperience)
{
	CurrentDamageExperience += DamageExperience;
	LevelUpDamage();
}

void ABigModeGameJam2025GameMode::LevelUpHealth()
{
	float RequiredExperience = BaseHealthExperienceThreshold * FMath::Pow(HealthExperienceMultiplier, GetCurrentHealthLevel());

	int32 PrevLevel = CurrentDamageLevel;
	while(CurrentHealthExperience >= RequiredExperience)
	{
		CurrentHealthExperience -= RequiredExperience;
		CurrentHealthLevel++;
		RequiredExperience = BaseHealthExperienceThreshold * FMath::Pow(HealthExperienceMultiplier, GetCurrentHealthLevel());

		UE_LOG(LogTemp, Log, TEXT("Leveled up Health. Level: %d"), CurrentHealthLevel);
	}
	//Update the players health here and all other related variables if we level Up

	
}

void ABigModeGameJam2025GameMode::LevelUpSpeed()
{
	float RequiredExperience = BaseSpeedExperienceThreshold * FMath::Pow(SpeedExperienceMultiplier, GetCurrentSpeedLevel());

	int32 PrevLevel = CurrentDamageLevel;
	while (CurrentSpeedExperience >= RequiredExperience)
	{
		CurrentSpeedExperience -= RequiredExperience;
		CurrentSpeedLevel++;
		RequiredExperience = BaseSpeedExperienceThreshold * FMath::Pow(SpeedExperienceMultiplier, GetCurrentSpeedLevel());

		UE_LOG(LogTemp, Log, TEXT("Leveled up Speed. Level: %d"), CurrentSpeedLevel);
	}
	//Update the players speed here and all other related variables if we level Up
	if(PrevLevel != CurrentSpeedLevel)
	{
		float NewSpeed = GetCurrentSpeed() + BASE_SPEED_REWARD;
		SetCurrentSpeed(NewSpeed);
	}
}

void ABigModeGameJam2025GameMode::LevelUpJumpVelocity()
{
	float RequiredExperience = BaseJumpVelocityExperienceThreshold * FMath::Pow(JumpVelocityExperienceMultiplier, GetCurrentJumpVelocityLevel());

	int32 PrevLevel = CurrentDamageLevel;
	while (CurrentJumpVelocityExperience >= RequiredExperience)
	{
		CurrentJumpVelocityExperience -= RequiredExperience;
		CurrentJumpVelocityLevel++;
		RequiredExperience = BaseJumpVelocityExperienceThreshold * FMath::Pow(JumpVelocityExperienceMultiplier, GetCurrentJumpVelocityLevel());

		UE_LOG(LogTemp, Log, TEXT("Leveled up Jump Velocity. Level: %d"), CurrentJumpVelocityLevel);
	}
	//Update the players jump velocity here and all other related variables if we level Up
	if(PrevLevel != CurrentJumpVelocityLevel)
	{
		float NewJumpVelocity = GetCurrentJumpVelocity() + BASE_JUMP_VELOCITY_REWARD;
		SetCurrentJumpVelocity(NewJumpVelocity);
	}

}

void ABigModeGameJam2025GameMode::LevelUpDamage()
{
	//float RequiredExperience = BaseDamageExperienceThreshold * FMath::Loge((double)GetCurrentDamageLevel() +1);
	float RequiredExperience = BaseDamageExperienceThreshold * FMath::Pow(DamageExperienceMultiplier, GetCurrentDamageLevel());
	int32 PrevLevel = CurrentDamageLevel;
	while (CurrentDamageExperience >= RequiredExperience)
	{
		CurrentDamageExperience -= RequiredExperience;
		CurrentDamageLevel++;
		//RequiredExperience = BaseDamageExperienceThreshold * FMath::Loge((double)GetCurrentDamageLevel() + 1);
		RequiredExperience = BaseDamageExperienceThreshold * FMath::Pow(DamageExperienceMultiplier, GetCurrentDamageLevel());

		UE_LOG(LogTemp, Log, TEXT("Leveled up Damage. Level: %d"), CurrentDamageLevel);
	}
	//Update the players damage here and all other related variables if we Level Up
	if(PrevLevel != CurrentDamageLevel)
	{
		float NewDamage = GetCurrentDamage() + BASE_DAMAGE_REWARD;
		SetCurrentDamage(NewDamage);
	}

}

int32 ABigModeGameJam2025GameMode::GetCurrentHealthLevel()
{
	return CurrentHealthLevel;
}

int32 ABigModeGameJam2025GameMode::GetCurrentSpeedLevel()
{
	return CurrentSpeedLevel;
}

int32 ABigModeGameJam2025GameMode::GetCurrentJumpVelocityLevel()
{
	return CurrentJumpVelocityLevel;
}

int32 ABigModeGameJam2025GameMode::GetCurrentDamageLevel()
{
	return CurrentDamageLevel;
}
