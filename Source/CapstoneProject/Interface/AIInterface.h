// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AIInterface.generated.h"

DECLARE_DELEGATE(FEnemyAttackFinished)
DECLARE_DELEGATE(FEnemySkill1Finished)

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAIInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CAPSTONEPROJECT_API IAIInterface
{
	GENERATED_BODY()

public:
	virtual float GetPatrolRadius() = 0;
	virtual float GetDetectRadius() = 0;
	virtual float GetAttackInRange() = 0;
	virtual float GetTurnSpeed() = 0;

	virtual void SetEnemyAttackDelegate(const FEnemyAttackFinished& InEnemyAttackFinished) = 0;
	virtual void SetEnemySkill1Delegate(const FEnemySkill1Finished& InEnemySkill1Finished) = 0;
	virtual void AttackByAI() = 0;
	virtual void DefaultAttackHitCheck() = 0;

	virtual void Skill1ByAI() = 0;
};
