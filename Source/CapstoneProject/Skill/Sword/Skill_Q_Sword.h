// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/SkillSword.h"
#include "Skill_Q_Sword.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROJECT_API USkill_Q_Sword : public USkillSword
{
	GENERATED_BODY()

public:
	USkill_Q_Sword();
	
	virtual void ExecuteSkill() override;
};
