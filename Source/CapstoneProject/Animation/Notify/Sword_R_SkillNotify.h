// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Sword_R_SkillNotify.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROJECT_API USword_R_SkillNotify : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	USword_R_SkillNotify();

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
