// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsPlayerInRange.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyCharacterBase.h"
#include "AIController.h"

UBTDecorator_IsPlayerInRange::UBTDecorator_IsPlayerInRange()
{
	NodeName = "Check if player is in range";
}

bool UBTDecorator_IsPlayerInRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    if (const UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent())
    {
        // Get the vectors from the blackboard
        FVector Vector1 = OwnerComp.GetOwner()->GetActorLocation();
        FVector Vector2 = BlackboardComp->GetValueAsVector(Vector2Key.SelectedKeyName);

        // Calculate the distance
        float Distance = FVector::Dist(Vector1, Vector2);
        AEnemyCharacterBase* Character = Cast<AEnemyCharacterBase>(OwnerComp.GetAIOwner()->GetPawn());
        // Return true if the distance is within the threshold
        return Distance <= Character->MeleeRange;
    }

    return false;
}

FString UBTDecorator_IsPlayerInRange::GetStaticDescription() const
{
	return FString("Returns True if 2 Given Vectors are in Enemy Range");
}
