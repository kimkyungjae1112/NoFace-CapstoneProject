// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/Skill_E_Base.h"
#include "Skill_E_UnConfirmed.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROJECT_API USkill_E_UnConfirmed : public USkill_E_Base
{
	GENERATED_BODY()

public:
	USkill_E_UnConfirmed();

	virtual void ExecuteSkill() override;
};
