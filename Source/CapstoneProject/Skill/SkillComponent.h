// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkillComponent.generated.h"

DECLARE_DELEGATE(FParryingSign)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CAPSTONEPROJECT_API USkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USkillComponent();

protected:
	virtual void BeginPlay() override;
	
public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FORCEINLINE bool GetCastingFlag() { return bCasting; }
	FORCEINLINE void SetCastingFlag(bool InCasting) { bCasting = InCasting; }
public:
	FParryingSign ParryingSign;
	void ParryingSuccess(AActor* Attacker);

	void PlaySkill_Q();
	void PlaySkill_W();
	void PlaySkill_E();
	void PlaySkill_R();

	void SetWeaponType(const int32& InCurrentWeaponType);

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
	void BeginStaffMeteor();
	void EndStaffMeteor(class UAnimMontage* Target, bool IsProperlyEnded);
	void BeginStaffArea();
	void EndStaffArea(class UAnimMontage* Target, bool IsProperlyEnded);
	void BeginStaffUpGround();
	void EndStaffUpGround(class UAnimMontage* Target, bool IsProperlyEnded);
	void BeginStaffThunderbolt();
	void EndStaffThunderbolt(class UAnimMontage* Target, bool IsProperlyEnded);

	UPROPERTY(EditAnywhere, Category = "Montage")
	TObjectPtr<class UCharacterSkillMontageData> SkillMontageData;

	FHitResult Cursor;
	bool bCasting = false;

public:
	//현재 캐스팅되는 스킬을 담을 컨테이너
	TQueue<TFunction<void()>> SkillQueue;

/* Bow 데이터 */
private:
	UPROPERTY(EditAnywhere, Category = "Bow")
	TObjectPtr<class UParticleSystem> RainArrows;

/* Staff 데이터 */
private:
	UPROPERTY(EditAnywhere, Category = "Staff")
	TSubclassOf<class AStaffMeteor> MeteorClass;

	UPROPERTY(EditAnywhere, Category = "Staff")
	TSubclassOf<class AStaffArea> AreaClass;

	UPROPERTY(EditAnywhere, Category = "Staff")
	TSubclassOf<class AStaffUpGround> UpGroundClass;

	UPROPERTY(EditAnywhere, Category = "Staff")
	TSubclassOf<class AStaffThunderbolt> ThunderboltClass;

/* 유틸리티 */
private:
	UPROPERTY(VisibleAnywhere, Category = "Character")
	TObjectPtr<class ACharacter> Character;

	UPROPERTY(VisibleAnywhere, Category = "Character")
	TObjectPtr<class APlayerController> PlayerController;

	int32 CurrentWeaponType = 0;
	
};
