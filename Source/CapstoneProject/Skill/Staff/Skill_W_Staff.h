// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/SkillStaff.h"
#include "Skill_W_Staff.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROJECT_API ASkill_W_Staff : public ASkillStaff
{
	GENERATED_BODY()

public:
	ASkill_W_Staff();

	virtual void ExecuteSkill() override;
};
