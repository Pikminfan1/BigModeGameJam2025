// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_IsPlayerInRange.generated.h"

/**
 * 
 */
UCLASS()
class BIGMODEGAMEJAM2025_API UBTDecorator_IsPlayerInRange : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTDecorator_IsPlayerInRange();

protected:
    /** Called each tick to evaluate the condition */
    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

    /** Used to describe the decorator in the Behavior Tree Editor */
    virtual FString GetStaticDescription() const override;
public:


    /** Blackboard key for the second vector */
    UPROPERTY(EditAnywhere, Category = "Blackboard")
    FBlackboardKeySelector Vector2Key;


};
