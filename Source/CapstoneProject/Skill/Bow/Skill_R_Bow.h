// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/Skill_R_Base.h"
#include "Skill_R_Bow.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROJECT_API USkill_R_Bow : public USkill_R_Base
{
	GENERATED_BODY()

public:
	USkill_R_Bow();

	virtual void ExecuteSkill() override;
	
};
