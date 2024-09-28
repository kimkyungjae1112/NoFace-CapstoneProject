// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyMelee_Tanker.h"
#include "AI/Controller/AIControllerTanker.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Stat/EnemyStatComponent.h"

AEnemyMelee_Tanker::AEnemyMelee_Tanker()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/SKnight_modular/Skeleton_Knight_02/mesh/SK_SKnigh_02_full.SK_SKnigh_02_full'"));
	if (MeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(MeshRef.Object);
	}
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));

}

void AEnemyMelee_Tanker::BeginPlay()
{
	Super::BeginPlay();

	
}
