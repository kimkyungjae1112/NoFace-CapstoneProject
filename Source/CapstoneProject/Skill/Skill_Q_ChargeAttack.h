// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/Skill_Q_Base.h"
#include "Skill_Q_ChargeAttack.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROJECT_API USkill_Q_ChargeAttack : public USkill_Q_Base
{
	GENERATED_BODY()
	
public:
	USkill_Q_ChargeAttack();

	virtual void ExecuteSkill() override;
};
