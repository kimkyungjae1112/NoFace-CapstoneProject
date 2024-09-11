// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/SkillBase.h"
#include "SkillStaff.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROJECT_API USkillStaff : public USkillBase
{
	GENERATED_BODY()

public:
	USkillStaff();

	virtual void ExecuteSkill() override;
	
};
