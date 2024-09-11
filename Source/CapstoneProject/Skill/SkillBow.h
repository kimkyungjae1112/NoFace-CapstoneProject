// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/SkillBase.h"
#include "SkillBow.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROJECT_API USkillBow : public USkillBase
{
	GENERATED_BODY()

public:
	USkillBow();

	virtual void ExecuteSkill() override;


};
