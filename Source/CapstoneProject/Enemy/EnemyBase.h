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

public:
	FMonsterAttackFinished MonsterAttackFinished;
	
	virtual float GetPatrolRadius() override;
	virtual float GetDetectRadius() override;
	virtual float GetAttackInRange() override;
	virtual float GetTurnSpeed() override;

	virtual void SetMonsterAttackDelegate(FMonsterAttackFinished InMonsterAttackFinished) override;
	virtual void AttackByAI() override;


/* 임시로 만든 공격 코드 차후 수정 예정 */
private:
	void BeginAttack();
	void EndAttack(class UAnimMontage* Target, bool IsProperlyEnded);

	UPROPERTY(EditAnywhere, Category = "Montage")
	TObjectPtr<class UAnimMontage> AttackMontage;
};
