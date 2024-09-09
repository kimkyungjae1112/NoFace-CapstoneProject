// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyBase.h"

AEnemyBase::AEnemyBase()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MainMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Manny.SKM_Manny'"));
	if (MainMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(MainMeshRef.Object);
	}

	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
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



