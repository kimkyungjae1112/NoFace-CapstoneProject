// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkillComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CAPSTONEPROJECT_API USkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USkillComponent();

protected:
	virtual void BeginPlay() override;

public:
	FORCEINLINE void SetHitCheckComponent(class UCharacterHitCheckComponent* InHitCheckComponent) { HitCheckComponent = InHitCheckComponent; }

	void PlaySkill_Q();
	void PlaySkill_W();
	void PlaySkill_E();
	void PlaySkill_R();

	void SetWeaponType(int32& InCurrentWeaponType);

private:
	//Sword Skill Montage
	void BeginSwordSting();
	void EndSwordSting(class UAnimMontage* Target, bool IsProperlyEnded);
	void BeginSwordWhirlwind();
	void EndSwordWhirlwind(class UAnimMontage* Target, bool IsProperlyEnded);
	void BeginSwordParrying();
	void EndSwordParrying(class UAnimMontage* Target, bool IsProperlyEnded);
	void BeginSwordAura();
	void EndSwordAura(class UAnimMontage* Target, bool IsProperlyEnded);

	//Bow Skill Montage
	void BeginBowSeveralArrows();
	void EndBowSeveralArrows(class UAnimMontage* Target, bool IsProperlyEnded);
	void BeginBowExplosionArrow();
	void EndBowExplosionArrow(class UAnimMontage* Target, bool IsProperlyEnded);
	void BeginBowBackstep();
	void EndBowBackstep(class UAnimMontage* Target, bool IsProperlyEnded);
	void BeginBowAutoTargeting();
	void EndBowAutoTargeting(class UAnimMontage* Target, bool IsProperlyEnded);

	//Staff Skill Montage
	void BeginStaffFireball();
	void EndStaffFireball(class UAnimMontage* Target, bool IsProperlyEnded);
	void BeginStaffArea();
	void EndStaffArea(class UAnimMontage* Target, bool IsProperlyEnded);
	void BeginStaffUpGround();
	void EndStaffUpGround(class UAnimMontage* Target, bool IsProperlyEnded);
	void BeginStaffThunderbolt();
	void EndStaffThunderbolt(class UAnimMontage* Target, bool IsProperlyEnded);

	UPROPERTY(EditAnywhere, Category = "Montage")
	TObjectPtr<class UCharacterSkillMontageData> SkillMontageData;

	UPROPERTY(VisibleAnywhere, Category = "Character")
	TObjectPtr<class ACharacter> Character;
	
	int32 CurrentWeaponType = 0;

private:
	UPROPERTY(VisibleAnywhere, Category = "Hit Check")
	TObjectPtr<class UCharacterHitCheckComponent> HitCheckComponent;
};
