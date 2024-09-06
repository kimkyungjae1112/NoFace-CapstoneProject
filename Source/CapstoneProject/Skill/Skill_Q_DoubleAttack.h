// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/Skill_Q_Base.h"
#include "Skill_Q_DoubleAttack.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROJECT_API USkill_Q_DoubleAttack : public USkill_Q_Base
{
	GENERATED_BODY()
	
public:
	USkill_Q_DoubleAttack();

	virtual void ExecuteSkill() override;
};
