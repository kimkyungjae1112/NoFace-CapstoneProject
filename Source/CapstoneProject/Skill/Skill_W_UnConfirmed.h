// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/Skill_W_Base.h"
#include "Skill_W_UnConfirmed.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROJECT_API USkill_W_UnConfirmed : public USkill_W_Base
{
	GENERATED_BODY()

public:
	USkill_W_UnConfirmed();

	virtual void ExecuteSkill() override;
	
};