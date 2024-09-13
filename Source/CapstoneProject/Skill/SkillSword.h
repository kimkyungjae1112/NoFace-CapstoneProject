// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/SkillBase.h"
#include "SkillSword.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROJECT_API ASkillSword : public ASkillBase
{
	GENERATED_BODY()
	
public:
	ASkillSword();

	virtual void ExecuteSkill() override;
};
