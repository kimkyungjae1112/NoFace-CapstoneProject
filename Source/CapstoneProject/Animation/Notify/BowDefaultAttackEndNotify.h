// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "BowDefaultAttackEndNotify.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROJECT_API UBowDefaultAttackEndNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	UBowDefaultAttackEndNotify();

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
};
