// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyBase.h"

AEnemyBase::AEnemyBase()
{

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



