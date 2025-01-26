// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Melee.h"
#include "AIController.h"
#include "EnemyCharacterBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
UBTTask_Melee::UBTTask_Melee()
{
    bNotifyTick = true;
	NodeName = "Melee";
}

EBTNodeResult::Type UBTTask_Melee::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() == nullptr) {
		return EBTNodeResult::Failed;
	}
	AEnemyCharacterBase* Character = Cast<AEnemyCharacterBase>(OwnerComp.GetAIOwner()->GetPawn());
	if (Character == nullptr) {
		return EBTNodeResult::Failed;
	}
    AActor* PlayerActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    float DistanceToPlayer = FVector::Dist(OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation(), PlayerActor->GetActorLocation());
    if (DistanceToPlayer > Character->MeleeRange)
    {
        UE_LOG(LogTemp, Warning, TEXT("Player moved out of range. Cancelling melee attack."));
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed); // Abort the task
        return EBTNodeResult::Failed;
    }
	Character->MeleeAttack();
	return EBTNodeResult::InProgress;
}

void UBTTask_Melee::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    if (OwnerComp.GetAIOwner() == nullptr)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }
    AEnemyCharacterBase* Character = Cast<AEnemyCharacterBase>(OwnerComp.GetAIOwner()->GetPawn());
    // Get the player character (assuming player is at index 0)
    AActor* PlayerActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (!PlayerActor)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    // Calculate the distance to the player
    float DistanceToPlayer = FVector::Dist(OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation(), PlayerActor->GetActorLocation());
    if (DistanceToPlayer > Character->MeleeRange)
    {
        UE_LOG(LogTemp, Warning, TEXT("Player moved out of range. Cancelling melee attack."));
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed); // Abort the task
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("Player is within range. Continuing melee attack."));
}
