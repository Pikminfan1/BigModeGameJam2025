// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeAttackAnimNotify.h"
#include "EnemyCharacterBase.h"

void UMeleeAttackAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if(MeshComp && MeshComp->GetOwner())
	{
		AEnemyCharacterBase* Enemy = Cast<AEnemyCharacterBase>(MeshComp->GetOwner());
		if(Enemy)
		{
			// Call the function to check if the player is in range
			Enemy->PerformMeleeHitCheck();
		}
	}
}
