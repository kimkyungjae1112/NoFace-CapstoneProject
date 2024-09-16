// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/SwordDefaultAttackInterface.h"
#include "CharacterHitCheckComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CAPSTONEPROJECT_API UCharacterHitCheckComponent : public UActorComponent, public ISwordDefaultAttackInterface
{
	GENERATED_BODY()

public:	
	UCharacterHitCheckComponent();

protected:
	virtual void BeginPlay() override;

/* 유틸리티 */
public:
	void SetWeaponType(int32& InCurrentWeaponType);


/* 검 히트 체크 */
public:
	virtual void SwordDefaultAttackHitCheck() override;
	virtual void Sword_Q_SkillHitCheck() override;

/* 검 히트 체크 */
private:
	bool SwordDefaultAttackRadialRange(AActor* Player, AActor* Target, float Radius, float RadialAngle);
	void SwordDefaultAttackHitDebug(UWorld* World, const FVector& Start, const FVector& ForwardVector, const float AttackRange, const FColor& Color);

private:
	UPROPERTY(EditAnywhere, Category = "Stat")
	TObjectPtr<class UCharacterDataStat> Stat;

	int32 CurrentWeaponType = 0;

};
