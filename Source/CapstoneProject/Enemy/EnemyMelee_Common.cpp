// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyMelee_Common.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Stat/CharacterDataStat.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"

AEnemyMelee_Common::AEnemyMelee_Common()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonMinions/Characters/Minions/Dusk_Minions/Meshes/Minion_Lane_Melee_Dusk.Minion_Lane_Melee_Dusk'"));
	if (MeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(MeshRef.Object);
	}
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	
	/* 콜리전 설정 */
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));
}

void AEnemyMelee_Common::AttackByAI()
{
	Super::AttackByAI();

	BeginAttack();
}

void AEnemyMelee_Common::DefaultAttackHitCheck()
{
	Super::DefaultAttackHitCheck();

}

float AEnemyMelee_Common::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	return Damage;
}

void AEnemyMelee_Common::Stun()
{
	Super::Stun();

}

void AEnemyMelee_Common::BeginAttack()
{
	UAnimInstance* AnimInstance = Cast<UAnimInstance>(GetMesh()->GetAnimInstance());

	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	AnimInstance->Montage_Play(DefaultAttackMontage);

	FOnMontageEnded MontageEnd;
	MontageEnd.BindUObject(this, &AEnemyMelee_Common::EndAttack);
	AnimInstance->Montage_SetEndDelegate(MontageEnd, DefaultAttackMontage);
}

void AEnemyMelee_Common::EndAttack(UAnimMontage* Target, bool IsProperlyEnded)
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);

	EnemyAttackFinished.ExecuteIfBound();
}

void AEnemyMelee_Common::BeingHitAction()
{
}

void AEnemyMelee_Common::SetDead()
{
}

void AEnemyMelee_Common::EndStun(UAnimMontage* Target, bool IsProperlyEnded)
{
}
