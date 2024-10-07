// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyRanged_Rifle.h"
#include "Components/CapsuleComponent.h"
#include "Stat/EnemyStatComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AI/Controller/AIControllerRifle.h"
#include "Engine/DamageEvents.h"

AEnemyRanged_Rifle::AEnemyRanged_Rifle()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonMinions/Characters/Minions/Dusk_Minions/Meshes/Minion_Lane_Ranged_Dusk.Minion_Lane_Ranged_Dusk'"));
	if (MeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(MeshRef.Object);
	}
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	/* 콜리전 설정 */
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));

	Stat->OnHpZero.AddUObject(this, &AEnemyRanged_Rifle::SetDead);

	SetRunSpeed();
}

void AEnemyRanged_Rifle::AttackByAI()
{
	Super::AttackByAI();
	
	BeginAttack();
}

void AEnemyRanged_Rifle::DefaultAttackHitCheck()
{
	Super::DefaultAttackHitCheck();

	float Damage = 50.f;
	float Range = 1000.f;

	FVector Origin = GetActorLocation();
	FVector End = Origin + GetActorForwardVector() * Range;
	FCollisionQueryParams Param(NAME_None, false, this);
	FHitResult HitResult;

	FVector ForwardVector = GetActorForwardVector() * Range;
	FQuat RootRot = FRotationMatrix::MakeFromZ(ForwardVector).ToQuat();
	FVector BoxExtent = FVector(100.f, 100.f, 100.f);

	bool bHit = GetWorld()->SweepSingleByChannel(HitResult, Origin, End, RootRot, ECC_GameTraceChannel1, FCollisionShape::MakeBox(BoxExtent), Param);
	if (bHit)
	{
		FDamageEvent DamageEvent;
		HitResult.GetActor()->TakeDamage(Damage, DamageEvent, GetController(), this);
	}

	DrawDebugBox(GetWorld(), Origin, BoxExtent, FColor::Green, false, 3.f);
	DrawDebugBox(GetWorld(), End, BoxExtent, FColor::Green, false, 3.f);
}

float AEnemyRanged_Rifle::GetPatrolRadius()
{
	return 500.f;
}

float AEnemyRanged_Rifle::GetDetectRadius()
{
	return 1500.f;
}

float AEnemyRanged_Rifle::GetAttackInRange()
{
	return 1000.f;
}

float AEnemyRanged_Rifle::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	BeginHitAction();

	Stat->ApplyDamage(Damage);

	return Damage;
}

float AEnemyRanged_Rifle::TakeExp()
{
	Super::TakeExp();

	return 60.0f;
}

void AEnemyRanged_Rifle::Stun()
{
	Super::Stun();

	UAnimInstance* AnimInstance = Cast<UAnimInstance>(GetMesh()->GetAnimInstance());

	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	AnimInstance->Montage_Play(StunMontage);

	FOnMontageEnded MontageEnd;
	MontageEnd.BindUObject(this, &AEnemyRanged_Rifle::EndStun);
	AnimInstance->Montage_SetEndDelegate(MontageEnd, StunMontage);
}

void AEnemyRanged_Rifle::SetDead()
{
	Super::SetDead();

	GetMyController()->StopAI();

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

	AnimInstance->StopAllMontages(5.f);
	AnimInstance->Montage_Play(DeadMontage);
	SetActorEnableCollision(false);

	FTimerHandle DestroyHandle;
	GetWorld()->GetTimerManager().SetTimer(DestroyHandle,
		[&]()
		{
			Destroy();
		}, 4.f, false);
}

void AEnemyRanged_Rifle::SetWalkSpeed()
{
	GetCharacterMovement()->MaxWalkSpeed = 210.f;
}

void AEnemyRanged_Rifle::SetRunSpeed()
{
	GetCharacterMovement()->MaxWalkSpeed = 420.f;
}

void AEnemyRanged_Rifle::BeginAttack()
{
	UAnimInstance* Anim = GetMesh()->GetAnimInstance();

	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	Anim->Montage_Play(DefaultAttackMontage);

	FOnMontageEnded MontageEnd;
	MontageEnd.BindUObject(this, &AEnemyRanged_Rifle::EndAttack);
	Anim->Montage_SetEndDelegate(MontageEnd, DefaultAttackMontage);
}

void AEnemyRanged_Rifle::EndAttack(UAnimMontage* Target, bool IsProperlyEnded)
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);

	EnemyAttackFinished.ExecuteIfBound();
}

void AEnemyRanged_Rifle::BeginHitAction()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

	/* 스턴 상태라면 그대로 진행 */
	if (AnimInstance->Montage_IsPlaying(StunMontage) || AnimInstance->Montage_IsPlaying(Skill1Montage))
	{
		return;
	}

	AnimInstance->Montage_Play(HitMontage);
}

void AEnemyRanged_Rifle::EndStun(UAnimMontage* Target, bool IsProperlyEnded)
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

AAIControllerRifle* AEnemyRanged_Rifle::GetMyController()
{
	return CastChecked<AAIControllerRifle>(GetController());
}
