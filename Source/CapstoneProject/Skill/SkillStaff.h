// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/SkillBase.h"
#include "SkillStaff.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROJECT_API ASkillStaff : public ASkillBase
{
	GENERATED_BODY()

public:
	ASkillStaff();

	virtual void ExecuteSkill() override;
	
};
