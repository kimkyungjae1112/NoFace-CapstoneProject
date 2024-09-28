// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyBase.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "AI/Controller/AIControllerBase.h"
#include "Components/CapsuleComponent.h"
#include "Stat/EnemyStatComponent.h"

AEnemyBase::AEnemyBase()
{
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));

	Stat = CreateDefaultSubobject<UEnemyStatComponent>(TEXT("Stat"));
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
}

float AEnemyBase::GetPatrolRadius()
{
	return 800.0f;
}

float AEnemyBase::GetDetectRadius()
{
	return 600.0f;
}

float AEnemyBase::GetAttackInRange()
{
	return 200.0f;
}

float AEnemyBase::GetTurnSpeed()
{
	return 10.0f;
}

void AEnemyBase::SetMonsterAttackDelegate(FEnemyAttackFinished InMonsterAttackFinished)
{
	EnemyAttackFinished = InMonsterAttackFinished;
}

void AEnemyBase::AttackByAI()
{
	UE_LOG(LogTemp, Display, TEXT("몬스터 공격"));

}

void AEnemyBase::DefaultAttackHitCheck()
{
}

void AEnemyBase::Stun()
{
	UE_LOG(LogTemp, Display, TEXT("스턴상태!!!!!!!!!!!"));
}







