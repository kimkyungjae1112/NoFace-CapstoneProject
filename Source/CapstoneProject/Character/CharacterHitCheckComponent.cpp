// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterHitCheckComponent.h"
#include "Stat/CharacterDataStat.h"
#include "Engine/OverlapResult.h"
#include "Engine/DamageEvents.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "Skill/SwordAura.h"

UCharacterHitCheckComponent::UCharacterHitCheckComponent()
{
	static ConstructorHelpers::FObjectFinder<UCharacterDataStat> StatRef(TEXT("/Script/CapstoneProject.CharacterDataStat'/Game/No-Face/Character/Stat/DA_CharacterStatData.DA_CharacterStatData'"));
	if (StatRef.Object)
	{
		Stat = StatRef.Object;
	}

}


void UCharacterHitCheckComponent::BeginPlay()
{
	Super::BeginPlay();

	Character = CastChecked<ACharacter>(GetOwner());
}

void UCharacterHitCheckComponent::SwordDefaultAttackHitCheck()
{
	const float AttackDamage = Stat->SwordDamage;
	const float AttackRange = Stat->SwordRange;
	const float AttackDegree = Stat->SwordDegree;

	FColor Color = FColor::Red;

	FVector Origin = Character->GetActorLocation();
	FVector ForwardVector = Character->GetActorForwardVector();
	FCollisionQueryParams Params(NAME_None, false, Character); 
	TArray<FOverlapResult> OverlapResults;

	//Range를 반지름으로 하고 캐릭터가 중심인 원 안에 Enemy Trace에 대해 Block으로 설정된 폰들을 찾는다.
	bool bHit = GetWorld()->OverlapMultiByChannel(OverlapResults, Origin, FQuat::Identity, ECC_GameTraceChannel2, FCollisionShape::MakeSphere(AttackRange), Params);
	if (bHit) //원 안에 들어 왔다면
	{
		for (const auto& OverlapResult : OverlapResults)
		{
			FDamageEvent DamageEvent;
			//설정된 Degree 값 안에 있는지 한번 더 확인을 거친다.
			//부채꼴의 공격 판정이 만들어짐
			if (SwordDefaultAttackRadialRange(GetOwner(), OverlapResult.GetActor(), AttackDegree))
			{   
				OverlapResult.GetActor()->TakeDamage(AttackDamage, DamageEvent, GetWorld()->GetFirstPlayerController(), Character);
				Color = FColor::Green;
			}
		}
	}

	//공격 범위 라인으로 나타내기
	SwordDefaultAttackHitDebug(Origin, ForwardVector, AttackRange, Color, AttackDegree);
}

void UCharacterHitCheckComponent::Sword_Q_SkillHitCheck()
{
	FColor Color = FColor::Red;

	FVector Origin = Character->GetActorLocation() + Character->GetActorForwardVector() * Character->GetCapsuleComponent()->GetScaledCapsuleRadius();
	FVector End = Origin + (Character->GetActorForwardVector() * Stat->Sword_Q_Range);
	FVector CapsuleExtend = FVector(200.f, 50.f, 50.f);
	FCollisionQueryParams Params(NAME_None, false, Character);
	TArray<FHitResult> HitResults;

	bool bHit = GetWorld()->SweepMultiByChannel(HitResults, Origin, End, FRotationMatrix::MakeFromZ(Character->GetActorForwardVector()).ToQuat(), ECC_GameTraceChannel2, FCollisionShape::MakeCapsule(CapsuleExtend), Params);
	if (bHit)
	{
		FDamageEvent DamageEvent;
		for (const auto& HitResult : HitResults)
		{
			HitResult.GetActor()->TakeDamage(100.f, DamageEvent, GetWorld()->GetFirstPlayerController(), Character);
			Color = FColor::Green;
		}
	}

	DrawDebugCapsule(GetWorld(),
		(Origin + End) * 0.5f,  
		(End - Origin).Size() * 0.5f,
		CapsuleExtend.Y,        
		FRotationMatrix::MakeFromZ(Character->GetActorForwardVector()).ToQuat(),
		Color,
		false,                 
		3.f                  
	);
}

void UCharacterHitCheckComponent::Sword_W_SkillHitCheck()
{
	const float Damage = Stat->Sword_W_Damage;
	const float Radius = Stat->Sword_W_Range;

	FColor Color = FColor::Red;

	FVector Origin = Character->GetActorLocation();
	FCollisionQueryParams Params(NAME_None, true, Character);
	TArray<FOverlapResult> OverlapResults;

	bool bHit = GetWorld()->OverlapMultiByChannel(OverlapResults, Origin, FQuat::Identity, ECC_GameTraceChannel2, FCollisionShape::MakeSphere(Radius), Params);
	if (bHit)
	{
		FDamageEvent DamageEvent;
		for (const auto& OverlapResult : OverlapResults)
		{
			OverlapResult.GetActor()->TakeDamage(Damage, DamageEvent, GetWorld()->GetFirstPlayerController(), Character);
			Color = FColor::Green;
		}
	}
	DrawDebugSphere(GetWorld(), Origin, Radius, 32, Color, false, 3.f);
}

void UCharacterHitCheckComponent::Sword_R_SkillHitCheck()
{
	AActor* Owner = GetOwner();
	if (Owner == nullptr) return;

	FVector SpawnLocation = Owner->GetActorLocation() + Owner->GetActorForwardVector() * 100.f;
	FRotator SpawnRotation = Owner->GetActorRotation();

	ASwordAura* SwordAura = GetWorld()->SpawnActor<ASwordAura>(SwordAuraClass, SpawnLocation, SpawnRotation);
	SwordAura->SetOwner(Owner);
	SwordAura->Init(Owner->GetActorForwardVector());
}

bool UCharacterHitCheckComponent::SwordDefaultAttackRadialRange(AActor* Player, AActor* Target, float RadialAngle)
{
	if (!Player || !Target) return false;

	FVector PlayerLocation = Player->GetActorLocation();
	FVector TargetLocation = Target->GetActorLocation();
	FVector ForwardVector = Player->GetActorForwardVector();
	FVector DirectionToTarget = (TargetLocation - PlayerLocation).GetSafeNormal();

	// 타겟이 부채꼴 각도 내에 있는지 확인
	float DotProduct = FVector::DotProduct(ForwardVector, DirectionToTarget);
	float AngleToTarget = FMath::Acos(DotProduct);

	// 라디안에서 각도로 변환
	float AngleToTargetDegrees = FMath::RadiansToDegrees(AngleToTarget);

	return AngleToTargetDegrees <= (RadialAngle / 2.0f);
}

void UCharacterHitCheckComponent::SwordDefaultAttackHitDebug(const FVector& Start, const FVector& ForwardVector, const float AttackRange, const FColor& Color, const float Degree)
{
	// 부채꼴의 두 끝점 계산
	FVector LeftVector = ForwardVector.RotateAngleAxis(-Degree/ 2.0f, FVector::UpVector);
	FVector RightVector = ForwardVector.RotateAngleAxis(Degree / 2.0f, FVector::UpVector);

	FVector LeftEndpoint = Start + LeftVector * AttackRange;
	FVector RightEndpoint = Start + RightVector * AttackRange;

	// 부채꼴의 중심선
	DrawDebugLine(GetWorld(), Start, Start + ForwardVector * AttackRange, Color, false, 3.0f);

	// 부채꼴의 두 끝선
	DrawDebugLine(GetWorld(), Start, LeftEndpoint, Color, false, 3.0f);
	DrawDebugLine(GetWorld(), Start, RightEndpoint, Color, false, 3.0f);
}

void UCharacterHitCheckComponent::SetWeaponType(int32& InCurrentWeaponType)
{
	CurrentWeaponType = InCurrentWeaponType;
}
