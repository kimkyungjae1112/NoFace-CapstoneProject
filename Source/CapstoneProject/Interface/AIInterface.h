// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AIInterface.generated.h"

DECLARE_DELEGATE(FEnemyAttackFinished)

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

	virtual void SetMonsterAttackDelegate(FEnemyAttackFinished InEnemyAttackFinished) = 0;
	virtual void AttackByAI() = 0;
};
