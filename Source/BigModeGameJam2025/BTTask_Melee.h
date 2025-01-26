// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Melee.generated.h"

/**
 * 
 */
UCLASS()
class BIGMODEGAMEJAM2025_API UBTTask_Melee : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_Melee();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
