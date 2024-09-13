// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/SkillBow.h"
#include "Skill_R_Bow.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROJECT_API ASkill_R_Bow : public ASkillBow
{
	GENERATED_BODY()

public:
	ASkill_R_Bow();

	virtual void ExecuteSkill() override;
	
};
