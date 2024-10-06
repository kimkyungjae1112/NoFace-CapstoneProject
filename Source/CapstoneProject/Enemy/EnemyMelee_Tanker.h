// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/EnemyBase.h"
#include "EnemyMelee_Tanker.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROJECT_API AEnemyMelee_Tanker : public AEnemyBase
{
	GENERATED_BODY()
	
public:
	AEnemyMelee_Tanker();

protected:
	virtual void BeginPlay() override;

public:
	/* AI 인터페이스 구현 섹션 */
	virtual void AttackByAI() override;
	virtual void DefaultAttackHitCheck() override;

	virtual void Skill1ByAI() override;

	/* 오버라이딩 섹션 */
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual float TakeExp() override;
	virtual void Stun() override;
	virtual void SetDead() override;


	///* 속도 조절, PlayerController 에서 호출 */
	//void SetWalkSpeed();
	//void SetRunSpeed();

private:
	void BeginAttack();
	void EndAttack(class UAnimMontage* Target, bool IsProperlyEnded);

	void BeginHitAction();

	/* 스킬 함수들 */
	void BeginSkill1();
	void EndSkill1(class UAnimMontage* Target, bool IsProperlyEnded);

	/* 스턴 애니메이션 끝날 때 실행되는 함수 */
	void EndStun(class UAnimMontage* Target, bool IsProperlyEnded);

	/* 기본 공격할 때 특정 각도 안에 플레이어(타겟)이 들어있는지 검증 함수 */
	bool IsInDegree(AActor* Actor, AActor* Target, float RadialAngle);
	void DefaultAttackHitDebug(const FVector& Start, const FVector& ForwardVector, const float AttackRange, const float AttackDegree, const FColor& Color);

	

/* 유틸리티 섹션 */
private:
	class AAIControllerTanker* GetMyController();


/* 몽타주 섹션 */
private:
	UPROPERTY(EditAnywhere, Category = "Montage")
	TObjectPtr<class UAnimMontage> DefaultAttackMontage;

	UPROPERTY(EditAnywhere, Category = "Montage")
	TObjectPtr<class UAnimMontage> DeadMontage;

	UPROPERTY(EditAnywhere, Category = "Montage")
	TObjectPtr<class UAnimMontage> HitMontage;

	UPROPERTY(EditAnywhere, Category = "Montage")
	TObjectPtr<class UAnimMontage> StunMontage;

	UPROPERTY(EditAnywhere, Category = "Montage")
	TObjectPtr<class UAnimMontage> Skill1Montage;

};
