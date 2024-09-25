// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Bow_W_SkillNotify.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROJECT_API UBow_W_SkillNotify : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	UBow_W_SkillNotify();

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
