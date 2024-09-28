// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyTest.h"
#include "AI/Controller/AIControllerBase.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/OverlapResult.h"
#include "Engine/DamageEvents.h"
#include "Stat/EnemyStatComponent.h"

AEnemyTest::AEnemyTest()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MainMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/No-Face/Character/Mesh/SKM_Quinn_Simple.SKM_Quinn_Simple'"));
	if (MainMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(MainMeshRef.Object);
	}

	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));

	Stat->OnHpZero.AddUObject(this, &AEnemyTest::SetDead);
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
	return Damage;
}

void AEnemyTest::DefaultAttackHitCheck()
{
	float Damage = Stat->GetCurrentDamage();
	float Range = Stat->GetCurrentRange();

	FColor Color(FColor::Red);
	FVector Origin = GetActorLocation();
	FCollisionQueryParams Params(NAME_None, true, this);
	TArray<FOverlapResult> OverlapResults;

	bool bHit = GetWorld()->OverlapMultiByChannel(OverlapResults, Origin, FQuat::Identity, ECC_GameTraceChannel1, FCollisionShape::MakeSphere(Range / 2.f), Params);
	if (bHit)
	{
		FDamageEvent DamageEvent;
		for (const auto& OverlapResult : OverlapResults)
		{
			OverlapResult.GetActor()->TakeDamage(50.f, DamageEvent, GetController(), this);
			Color = FColor::Green;
		}
	}

	DrawDebugSphere(GetWorld(), Origin, Range / 2.f, 16, Color, false, 3.f);
}

void AEnemyTest::Stun()
{
	Super::Stun();

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AAIControllerBase* AIController = Cast<AAIControllerBase>(GetController());

	if (AnimInstance && AIController)
	{
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
		AIController->StopAI();
		AnimInstance->Montage_Play(StunMontage);

		FOnMontageEnded MontageEnd;
		MontageEnd.BindUObject(this, &AEnemyTest::EndStun);
		AnimInstance->Montage_SetEndDelegate(MontageEnd, StunMontage);
	}

}
 
void AEnemyTest::BeginAttack()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AAIControllerBase* AIController = Cast<AAIControllerBase>(GetController());
	
	if (AnimInstance && AIController)
	{
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
		AnimInstance->Montage_Play(AttackMontage);

		FOnMontageEnded MontageEnd;
		MontageEnd.BindUObject(this, &AEnemyTest::EndAttack);
		AnimInstance->Montage_SetEndDelegate(MontageEnd, AttackMontage);
	}
}

void AEnemyTest::EndAttack(UAnimMontage* Target, bool IsProperlyEnded)
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);

	EnemyAttackFinished.ExecuteIfBound();
}

void AEnemyTest::BeingHitAction()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

	AnimInstance->Montage_Play(HitMontage);

	//피격 위치 및 피격 대미지, 무기 종류에 따라 다른 Hit 애니메이션이 나오는 것을 목표.
}

void AEnemyTest::SetDead()
{
	AAIControllerBase* AIController = Cast<AAIControllerBase>(GetController());
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AIController && AnimInstance)
	{
		AIController->StopAI();

		AnimInstance->StopAllMontages(1.0f);
		AnimInstance->Montage_Play(DeadMontage);
		SetActorEnableCollision(false);
	}
}

void AEnemyTest::EndStun(UAnimMontage* Target, bool IsProperlyEnded)
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	
	AAIControllerBase* AIController = Cast<AAIControllerBase>(GetController());
	AIController->RunAI();
}
