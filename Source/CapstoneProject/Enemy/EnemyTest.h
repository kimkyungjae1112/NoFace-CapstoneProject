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

/* AI 인터페이스 구현 섹션 */
	virtual void AttackByAI() override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void DefaultAttackHitCheck() override;

/* Base 클래스 가상 함수 구현 섹션 */
	virtual void Stun() override;

private:
	void BeginAttack();
	void EndAttack(class UAnimMontage* Target, bool IsProperlyEnded);
	
	void BeingHitAction();

	void SetDead();

private:
	void EndStun(class UAnimMontage* Target, bool IsProperlyEnded);

/* 몽타주 섹션 */
private:
	UPROPERTY(EditAnywhere, Category = "Montage")
	TObjectPtr<class UAnimMontage> AttackMontage;

	UPROPERTY(EditAnywhere, Category = "Montage")
	TObjectPtr<class UAnimMontage> HitMontage;

	UPROPERTY(EditAnywhere, Category = "Montage")
	TObjectPtr<class UAnimMontage> DeadMontage;

	UPROPERTY(EditAnywhere, Category = "Montage")
	TObjectPtr<class UAnimMontage> StunMontage;

};
