// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/AIInterface.h"
#include "EnemyBase.generated.h"

UCLASS()
class CAPSTONEPROJECT_API AEnemyBase : public ACharacter, public IAIInterface
{
	GENERATED_BODY()

public:
	AEnemyBase();

protected:
	virtual void BeginPlay() override;

/* AI 인터페이스 구현 섹션 */
public:
	FEnemyAttackFinished EnemyAttackFinished;
	
	virtual float GetPatrolRadius() override;
	virtual float GetDetectRadius() override;
	virtual float GetAttackInRange() override;
	virtual float GetTurnSpeed() override;

	virtual void SetMonsterAttackDelegate(FEnemyAttackFinished InEnemyAttackFinished) override;
	virtual void AttackByAI() override;
	virtual void DefaultAttackHitCheck() override;

public:
	void Stun();

};
