#pragma once

#include "CoreMinimal.h"
//#include "GameFramework/Character.h"
//#include "GlobalGameEnums.generated.h"


UENUM(BlueprintType)
enum class EGameState : uint8
{
	EGS_MainMenu,
	EGS_InGame,
	EGS_PauseMenu,
	EGS_OptionsMenu,
	EGS_QuitGame
};

//TODO: Move to AIController once created
// Used In AIController, should be moved there once AI Controller is created
UENUM(BlueprintType)
enum class EAISense : uint8
{
	EAIS_None UMETA(DisplayName = "None"),
	EAIS_Sight UMETA(DisplayName = "Sight"),
	EAIS_Hearing UMETA(DisplayName = "Hearing"),
	EAIS_Damage UMETA(DisplayName = "None"),
};

//TODO: Move to new file once created
//Used In Behavior Tree, should be moved to a new file once it is created
UENUM(BlueprintType)
enum class EAIState : uint8
{
	EAIS_None UMETA(DisplayName = "None"),
	EAIS_Passive UMETA(DisplayName = "Passive"),
	EAIS_Patrol UMETA(DisplayName = "Patrol"),
	EAIS_Attacking UMETA(DisplayName = "Attacking"),
	EAIS_Frozen UMETA(DisplayName = "Frozen"),
	EAIS_Dead UMETA(DisplayName = "Dead"),
	EAIS_Seeking UMETA(DisplayName = "Seeking"),
	EAIS_Investigating UMETA(DisplayName = "Investigating"),
};

//TODO: Move to new file once created
//Used In spawnmanager and gamemode, should be moved to a new file once it is created. Gamecomplete should
//be moved to gamemode enum
UENUM(BlueprintType)
enum class EArea : uint8
{
	EAREA_None UMETA(DisplayName = "None"),
	EAREA_Crypt_Area UMETA(DisplayName = "Crypt Area"),
	EAREA_Tomb_Area UMETA(DisplayName = "Tomb Area"),
	EAREA_Graveyard_Area UMETA(DisplayName = "Graveyard Area"),
	EAREA_Path_to_Church_Area UMETA(DisplayName = "Path to Church Area"),
	EAREA_Church_Area UMETA(DisplayName = "Church Area"),
	EAREA_GameCompleted UMETA(DisplayName = "Game Completed"),

};

//Global Enum for Determining Game Difficulty
UENUM(BlueprintType)
enum class EGameDifficulty : uint8
{
	EGD_Easy,
	EGD_Normal,
	EGD_Hard,
	EGD_Impossible
};

//TODO: Move to new file once created
//Enum for determinging a successful melee block, should be moved to enemy base once created
UENUM(BlueprintType)
enum class EBlockingState : uint8
{
	EBS_None UMETA(DisplayName = "None"),
	EBS_Blocking UMETA(DisplayName = "Blocking"),
	EBS_BlockedSuccessfully UMETA(DisplayName = "Blocked Successfully"),
	EBS_BlockedFailed UMETA(DisplayName = "Blocked Failed"),
};

//TODO: Move to new file once created
//Enum for determining the type of damage a character can take, should be moved to character once created
UENUM(BlueprintType)
enum class EDamageResponse : uint8
{
	EDR_None UMETA(DisplayName = "None"),
	EDR_HitReaction UMETA(DisplayName = "Hit Reaction"),
	EDR_Stagger UMETA(DisplayName = "Stagger"),
	EDR_Stunned UMETA(DisplayName = "Stunned"),
	EDR_Knockback UMETA(DisplayName = "Knockback"),
};

//TODO: Move to new file once created
//Enum for determining the type of damage a character can take, should be moved to Damage System once created
UENUM(BlueprintType)
enum class EDamageType : uint8
{
	EDT_None UMETA(DisplayName = "None"),
	EDT_Melee UMETA(DisplayName = "Melee"),
	EDT_Projectile UMETA(DisplayName = "Projectile"),
	EDT_Explosion UMETA(DisplayName = "Explosion"),
	EDT_Environmental UMETA(DisplayName = "Environmental"),
	EDT_Throw UMETA(DisplayName = "Throw"),
	EDT_Kick UMETA(DisplayName = "Kick"),
};

//TODO: Move to Gamemode once created
UENUM(BlueprintType)
enum class EGameComplete : uint8
{
	EGC_None UMETA(DisplayName = "None"),
	EGC_Completed UMETA(DisplayName = "Completed"),
	EGC_Failed UMETA(DisplayName = "Failed"),
};

//TODO: Move to new file once created
//Enum for determining the type of enemy, should be moved to enemy once created, might be merged with something else
UENUM(BlueprintType)
enum class EEnemyBonusType : uint8
{
	EEBT_None UMETA(DisplayName = "None"),
	EEBT_Health UMETA(DisplayName = "Health"),
	EEBT_Jump UMETA(DisplayName = "Jump"),
	EEBT_Speed UMETA(DisplayName = "Speed"),
};

//TODO: Move to new file once created
//Enum for determining enemy speed state, used in behavior tree. Should be moved to enemy once created
UENUM(BlueprintType)
enum class EMovementSpeedState : uint8
	{
	EMSS_None UMETA(DisplayName = "None"),
	EMSS_Idle UMETA(DisplayName = "Idle"),
	EMSS_Walking UMETA(DisplayName = "Walking"),
	EMSS_Jogging UMETA(DisplayName = "Jogging"),
	EMSS_Sprinting UMETA(DisplayName = "Sprinting"),
};

//TODO: Move to new file once created
//Enum for determining the type of player experience, should be moved to player or experience component once created
UENUM(BlueprintType)
enum class EPlayerExperienceType : uint8
{
	EPET_None UMETA(DisplayName = "None"),
	EPET_Jump UMETA(DisplayName = "Jump Experience"),
	EPET_Speed UMETA(DisplayName = "Speed Experience"),
	EPET_Kick UMETA(DisplayName = "Kick Experience"),
	EPET_Throw UMETA(DisplayName = "Throw Experience"),
	EPET_Gun UMETA(DisplayName = "Gun Experience"),

};

