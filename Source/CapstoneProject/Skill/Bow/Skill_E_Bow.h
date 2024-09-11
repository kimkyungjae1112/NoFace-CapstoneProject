// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/Skill_E_Base.h"
#include "Skill_E_Bow.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROJECT_API USkill_E_Bow : public USkill_E_Base
{
	GENERATED_BODY()

public:
	USkill_E_Bow();

	virtual void ExecuteSkill() override;
	
};
