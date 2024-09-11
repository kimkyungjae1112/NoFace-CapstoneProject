// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/Skill_R_Base.h"
#include "Skill_R_Sword.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROJECT_API USkill_R_Sword : public USkill_R_Base
{
	GENERATED_BODY()
	
public:
	USkill_R_Sword();

	virtual void ExecuteSkill() override;
};
