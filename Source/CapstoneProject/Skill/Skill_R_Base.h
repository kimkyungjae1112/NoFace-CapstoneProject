// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/SkillBase.h"
#include "Skill_R_Base.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROJECT_API USkill_R_Base : public USkillBase
{
	GENERATED_BODY()
	
public:
	USkill_R_Base();

	virtual void ExecuteSkill() override;
};
