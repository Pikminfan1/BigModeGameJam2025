// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyCharacterBase.h"

void AEnemyShooterAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

bool AEnemyShooterAIController::IsDead() const
{
	AEnemyCharacterBase* ControlledCharacter = Cast<AEnemyCharacterBase>(GetPawn());
	if (ControlledCharacter != nullptr) {
		return ControlledCharacter->IsDead();
	}
	return true;
}

void AEnemyShooterAIController::BeginPlay()
{
	Super::BeginPlay();
	if (AIBehavior != nullptr) {
		RunBehaviorTree(AIBehavior);

		APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	}
}
