// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/SwordInterface.h"
#include "CharacterHitCheckComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CAPSTONEPROJECT_API UCharacterHitCheckComponent : public UActorComponent, public ISwordInterface
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
	virtual void Sword_W_SkillHitCheck() override;
	virtual void Sword_R_SkillHitCheck() override;

/* 검 히트 체크 */
private:
	bool SwordDefaultAttackRadialRange(AActor* Player, AActor* Target, float RadialAngle);
	void SwordDefaultAttackHitDebug(const FVector& Start, const FVector& ForwardVector, const float AttackRange, const FColor& Color, const float Degree);

private:
	UPROPERTY(EditAnywhere, Category = "Stat")
	TObjectPtr<class UCharacterDataStat> Stat;

	int32 CurrentWeaponType = 0;

private:
	UPROPERTY(EditAnywhere, Category = "SwordAura")
	TSubclassOf<class ASwordAura> SwordAuraClass;

private:
	UPROPERTY(VisibleAnywhere, Category = "Character")
	TObjectPtr<class ACharacter> Character;

};
