// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EnemyDefaultAttackNotify.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROJECT_API UEnemyDefaultAttackNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	UEnemyDefaultAttackNotify();

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
};
