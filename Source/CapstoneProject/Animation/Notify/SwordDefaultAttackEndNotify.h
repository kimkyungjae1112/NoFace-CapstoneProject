// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "SwordDefaultAttackEndNotify.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROJECT_API USwordDefaultAttackEndNotify : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	USwordDefaultAttackEndNotify();

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
