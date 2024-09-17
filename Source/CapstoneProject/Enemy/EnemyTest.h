// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/EnemyBase.h"
#include "EnemyTest.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROJECT_API AEnemyTest : public AEnemyBase
{
	GENERATED_BODY()

public:
	AEnemyTest();

	virtual void AttackByAI() override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void DefaultAttackHitCheck() override;

private:
	void BeginAttack();
	void EndAttack(class UAnimMontage* Target, bool IsProperlyEnded);
	
	void BeingHitAction();

	void SetDead();

/* 몽타주 섹션 */
private:
	UPROPERTY(EditAnywhere, Category = "Montage")
	TObjectPtr<class UAnimMontage> AttackMontage;

	UPROPERTY(EditAnywhere, Category = "Montage")
	TObjectPtr<class UAnimMontage> HitMontage;

	UPROPERTY(EditAnywhere, Category = "Montage")
	TObjectPtr<class UAnimMontage> DeadMontage;

/* 스텟 섹션 */
private:
	UPROPERTY(EditAnywhere, Category = "Stat")
	TObjectPtr<class UCharacterStatComponent> Stat;
};
