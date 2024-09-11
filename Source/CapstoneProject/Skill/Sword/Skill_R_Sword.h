// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/SkillSword.h"
#include "Skill_R_Sword.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROJECT_API USkill_R_Sword : public USkillSword
{
	GENERATED_BODY()
	
public:
	USkill_R_Sword();

	virtual void ExecuteSkill() override;
};
