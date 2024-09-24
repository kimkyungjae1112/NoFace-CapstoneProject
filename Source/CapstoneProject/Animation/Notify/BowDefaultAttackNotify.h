// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "BowDefaultAttackNotify.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROJECT_API UBowDefaultAttackNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	UBowDefaultAttackNotify();

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
};
