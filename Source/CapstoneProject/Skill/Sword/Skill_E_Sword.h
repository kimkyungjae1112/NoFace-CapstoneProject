// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/SkillSword.h"
#include "Skill_E_Sword.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROJECT_API ASkill_E_Sword : public ASkillSword
{
	GENERATED_BODY()

public:
	ASkill_E_Sword();

	virtual void ExecuteSkill() override;
};
