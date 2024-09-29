// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/AIInterface.h"
#include "Interface/EnemyHpBarWidgetInterface.h"
#include "EnemyBase.generated.h"

UCLASS()
class CAPSTONEPROJECT_API AEnemyBase : public ACharacter, public IAIInterface, public IEnemyHpBarWidgetInterface
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

/* Widget */
	virtual void SetupHpBarWidget(class UEnemyHpBarWidget* InHpBarWidget) override;

/* Stun 은 보스 몬스터 말고 있을 것 같으니 상속받아 구현하자. */
public:
	virtual void Stun();
	
protected:
	UPROPERTY(VisibleAnywhere, Category = "Stat")
	TObjectPtr<class UEnemyStatComponent> Stat;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	TObjectPtr<class UWidgetComponent> HpBar;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UEnemyPtrWidget> HpBarClass;
};
