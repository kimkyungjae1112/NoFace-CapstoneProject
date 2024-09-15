// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterHitCheckComponent.h"
#include "Stat/CharacterDataStat.h"
#include "Engine/OverlapResult.h"
#include "Engine/DamageEvents.h"

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

	
}

void UCharacterHitCheckComponent::SetWeaponType(int32& InCurrentWeaponType)
{
	CurrentWeaponType = InCurrentWeaponType;
}

void UCharacterHitCheckComponent::SwordDefaultAttackHitCheck()
{
	AActor* Owner = GetOwner();
	if (Owner == nullptr) return;

	float AttackDamage = Stat->Damage;
	float AttackRange = Stat->Range;
	FColor Color = FColor::Red;

	FVector Origin = Owner->GetActorLocation();
	FVector ForwardVector = Owner->GetActorForwardVector();
	FCollisionQueryParams Params(NAME_None, false, Owner);
	TArray<FOverlapResult> OverlapResults;

	bool bHit = GetWorld()->OverlapMultiByChannel(OverlapResults, Origin, FQuat::Identity, ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(AttackRange), Params);
	if (bHit)
	{
		for (const auto& OverlapResult : OverlapResults)
		{
			FDamageEvent DamageEvent;
			if (SwordDefaultAttackRadialRange(Owner, OverlapResult.GetActor(), AttackRange, 60.f))
			{
				OverlapResult.GetActor()->TakeDamage(AttackDamage, DamageEvent, GetWorld()->GetFirstPlayerController(), Owner);
				Color = FColor::Green;
			}
		}
	}

	SwordDefaultAttackHitDebug(Owner->GetWorld(), Origin, ForwardVector, AttackRange, Color);
}

bool UCharacterHitCheckComponent::SwordDefaultAttackRadialRange(AActor* Player, AActor* Target, float Radius, float RadialAngle)
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

void UCharacterHitCheckComponent::SwordDefaultAttackHitDebug(UWorld* World, const FVector& Start, const FVector& ForwardVector, const float AttackRange, const FColor& Color)
{
	float AngleRadians = FMath::DegreesToRadians(60.f / 2.0f);

	// 부채꼴의 두 끝점 계산
	FVector LeftVector = ForwardVector.RotateAngleAxis(-60.f / 2.0f, FVector::UpVector);
	FVector RightVector = ForwardVector.RotateAngleAxis(60.f / 2.0f, FVector::UpVector);

	FVector LeftEndpoint = Start + LeftVector * AttackRange;
	FVector RightEndpoint = Start + RightVector * AttackRange;

	// 부채꼴의 중심선
	DrawDebugLine(GetWorld(), Start, Start + ForwardVector * AttackRange, Color, false, 3.0f);

	// 부채꼴의 두 끝선
	DrawDebugLine(GetWorld(), Start, LeftEndpoint, Color, false, 3.0f);
	DrawDebugLine(GetWorld(), Start, RightEndpoint, Color, false, 3.0f);
}



