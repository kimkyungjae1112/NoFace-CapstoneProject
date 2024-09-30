// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyMelee_Tanker.h"
#include "AI/Controller/AIControllerTanker.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Stat/EnemyStatComponent.h"
#include "Engine/OverlapResult.h"
#include "Engine/DamageEvents.h"

AEnemyMelee_Tanker::AEnemyMelee_Tanker()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/No-Face/Enemy/Skeleton_Knight_02/mesh/SK_SKnigh_02_full.SK_SKnigh_02_full'"));
	if (MeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(MeshRef.Object);
	}
	GetMesh()->SetRelativeRotation(FRotator(0.f, -180.f, 0.f));
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	WeaponMesh->SetupAttachment(GetMesh(), TEXT("hand_rSocket"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> WeaponMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/No-Face/Enemy/Skeleton_Knight_02/mesh/weapon/SK_weapon_02.SK_weapon_02'"));
	if (WeaponMeshRef.Object)
	{
		WeaponMesh->SetSkeletalMesh(WeaponMeshRef.Object);
	}

	ShieldMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Shield"));
	ShieldMesh->SetupAttachment(GetMesh(), TEXT("hand_lSocket"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> ShieldMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/No-Face/Enemy/Skeleton_Knight_02/mesh/weapon/SK_shield_02.SK_shield_02'"));
	if (ShieldMeshRef.Object)
	{
		ShieldMesh->SetSkeletalMesh(ShieldMeshRef.Object);
	}
}

void AEnemyMelee_Tanker::BeginPlay()
{
	Super::BeginPlay();

	Stat->OnHpZero.AddUObject(this, &AEnemyMelee_Tanker::SetDead);
}

void AEnemyMelee_Tanker::AttackByAI()
{
	Super::AttackByAI();

	BeginAttack();
}

void AEnemyMelee_Tanker::DefaultAttackHitCheck()
{
	Super::DefaultAttackHitCheck();

	const float Damage = Stat->GetCurrentDamage();
	const float Range = Stat->GetCurrentRange();
	const float Degree = 60.f;

	FColor Color = FColor::Red;
	FVector Origin = GetActorLocation();
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams Params(NAME_None, false, this);

	bool bHit = GetWorld()->OverlapMultiByChannel(OverlapResults, Origin, FQuat::Identity, ECC_GameTraceChannel1, FCollisionShape::MakeSphere(Range), Params);
	if (bHit)
	{
		for (const auto& OverlapResult : OverlapResults)
		{
			if (IsInDegree(this, OverlapResult.GetActor(), Degree))
			{
				FDamageEvent DamageEvent;
				OverlapResult.GetActor()->TakeDamage(Damage, DamageEvent, GetController(), this);
				Color = FColor::Green;
			}
		}
	}

	DefaultAttackHitDebug(Origin, GetActorForwardVector(), Range, Degree, Color);
}

float AEnemyMelee_Tanker::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	BeginHitAction();

	Stat->ApplyDamage(Damage);
	return 0.0f;
}

void AEnemyMelee_Tanker::Stun()
{
	Super::Stun();


}

void AEnemyMelee_Tanker::BeginAttack()
{
	UAnimInstance* AnimInstance = Cast<UAnimInstance>(GetMesh()->GetAnimInstance());

	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	AnimInstance->Montage_Play(DefaultAttackMontage);

	FOnMontageEnded MontageEnd;
	MontageEnd.BindUObject(this, &AEnemyMelee_Tanker::EndAttack);
	AnimInstance->Montage_SetEndDelegate(MontageEnd, DefaultAttackMontage);
}

void AEnemyMelee_Tanker::EndAttack(UAnimMontage* Target, bool IsProperlyEnded)
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);

	EnemyAttackFinished.ExecuteIfBound();
}

void AEnemyMelee_Tanker::BeginHitAction()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

	/* 스턴 상태라면 그대로 진행 */
	if (AnimInstance->Montage_IsPlaying(StunMontage))
	{
		return;
	}

	AnimInstance->Montage_Play(HitMontage);
}

void AEnemyMelee_Tanker::SetDead()
{
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

void AEnemyMelee_Tanker::EndStun(UAnimMontage* Target, bool IsProperlyEnded)
{
}

bool AEnemyMelee_Tanker::IsInDegree(AActor* Actor, AActor* Target, float RadialAngle)
{
	if (!Actor || !Target) return false;

	FVector PlayerLocation = Actor->GetActorLocation();
	FVector TargetLocation = Target->GetActorLocation();
	FVector ForwardVector = Actor->GetActorForwardVector();
	FVector DirectionToTarget = (TargetLocation - PlayerLocation).GetSafeNormal();

	// 타겟이 부채꼴 각도 내에 있는지 확인
	float DotProduct = FVector::DotProduct(ForwardVector, DirectionToTarget);
	float AngleToTarget = FMath::Acos(DotProduct);

	// 라디안에서 각도로 변환
	float AngleToTargetDegrees = FMath::RadiansToDegrees(AngleToTarget);

	return AngleToTargetDegrees <= (RadialAngle / 2.0f);
}

void AEnemyMelee_Tanker::DefaultAttackHitDebug(const FVector& Start, const FVector& ForwardVector, const float AttackRange, const float AttackDegree, const FColor& Color)
{
	// 부채꼴의 두 끝점 계산
	FVector LeftVector = ForwardVector.RotateAngleAxis(-AttackDegree / 2.0f, FVector::UpVector);
	FVector RightVector = ForwardVector.RotateAngleAxis(AttackDegree / 2.0f, FVector::UpVector);

	FVector LeftEndpoint = Start + LeftVector * AttackRange;
	FVector RightEndpoint = Start + RightVector * AttackRange;

	// 부채꼴의 중심선
	DrawDebugLine(GetWorld(), Start, Start + ForwardVector * AttackRange, Color, false, 3.0f);

	// 부채꼴의 두 끝선
	DrawDebugLine(GetWorld(), Start, LeftEndpoint, Color, false, 3.0f);
	DrawDebugLine(GetWorld(), Start, RightEndpoint, Color, false, 3.0f);
}

AAIControllerTanker* AEnemyMelee_Tanker::GetMyController()
{
	return CastChecked<AAIControllerTanker>(GetController());
}
