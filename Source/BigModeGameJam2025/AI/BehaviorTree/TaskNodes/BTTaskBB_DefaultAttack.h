// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTaskBB_DefaultAttack.generated.h"

/**
 * 
 */
UCLASS()
class BIGMODEGAMEJAM2025_API UBTTaskBB_DefaultAttack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	public:
		UBTTaskBB_DefaultAttack(FObjectInitializer const& ObjectInitializer = FObjectInitializer::Get());
		
		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
