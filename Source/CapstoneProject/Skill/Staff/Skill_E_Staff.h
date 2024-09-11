// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/SkillStaff.h"
#include "Skill_E_Staff.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROJECT_API USkill_E_Staff : public USkillStaff
{
	GENERATED_BODY()
	
public:
	USkill_E_Staff();

	virtual void ExecuteSkill() override;
};
