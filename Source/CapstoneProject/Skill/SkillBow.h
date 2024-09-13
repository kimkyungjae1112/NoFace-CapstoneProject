// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/SkillBase.h"
#include "SkillBow.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROJECT_API ASkillBow : public ASkillBase
{
	GENERATED_BODY()

public:
	ASkillBow();

	virtual void ExecuteSkill() override;


};
