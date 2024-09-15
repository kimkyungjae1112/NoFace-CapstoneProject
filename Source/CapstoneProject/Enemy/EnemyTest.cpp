// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyTest.h"
#include "AI/Controller/AIControllerBase.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "Stat/CharacterStatComponent.h"

AEnemyTest::AEnemyTest()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MainMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Manny.SKM_Manny'"));
	if (MainMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(MainMeshRef.Object);
	}

	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	/* 스텟 컴포넌트 초기화 */
	Stat = CreateDefaultSubobject<UCharacterStatComponent>(TEXT("Stat"));
}

void AEnemyTest::AttackByAI()
{
	BeginAttack();
}

float AEnemyTest::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	
	Stat->ApplyDamage(Damage);
	BeingHitAction();
	return 0.0f;
}

void AEnemyTest::BeginAttack()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

	AAIControllerBase* AIController = Cast<AAIControllerBase>(GetController());
	AIController->StopAI();
	AnimInstance->Montage_Play(AttackMontage);

	FOnMontageEnded MontageEnd;
	MontageEnd.BindUObject(this, &AEnemyTest::EndAttack);
	AnimInstance->Montage_SetEndDelegate(MontageEnd, AttackMontage);
}

void AEnemyTest::EndAttack(UAnimMontage* Target, bool IsProperlyEnded)
{
	AAIControllerBase* AIController = Cast<AAIControllerBase>(GetController());
	AIController->RunAI();
}

void AEnemyTest::BeingHitAction()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

	AnimInstance->Montage_Play(HitMontage);
}
