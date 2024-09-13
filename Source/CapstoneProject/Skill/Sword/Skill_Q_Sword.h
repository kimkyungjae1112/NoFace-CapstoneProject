// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/SkillSword.h"
#include "Skill_Q_Sword.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROJECT_API ASkill_Q_Sword : public ASkillSword
{
	GENERATED_BODY()

public:
	ASkill_Q_Sword();

public:
	virtual void ExecuteSkill() override;


};
