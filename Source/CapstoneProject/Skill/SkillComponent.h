// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/BowSkillInterface.h"
#include "SkillComponent.generated.h"

DECLARE_DELEGATE(FParryingSign)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CAPSTONEPROJECT_API USkillComponent : public UActorComponent, public IBowSkillInterface
{
	GENERATED_BODY()

public:	
	USkillComponent();

protected:
	virtual void BeginPlay() override;
	
public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/* 활 W, 스태프 Q, W, E 등 캐스팅이 필요한 스킬의 Flag의 Get, Set */
	FORCEINLINE bool GetCastingFlag() { return bCasting; }
	FORCEINLINE void SetCastingFlag(bool InCasting) { bCasting = InCasting; }

	/* 스킬 실행 중 무기 교체 방지 */
	FORCEINLINE bool CanChangeWeapon() { return bCanChangeWeapon; }

public:
	/* 패링 스킬이 실행되면 패링 플래그를 토글한다. */
	FParryingSign ParryingSign;

	/* 패링 성공시 실행될 함수, Attacker라는 공격을 한 적의 포인터를 인자로 받는다. */
	void ParryingSuccess(AActor* Attacker);

	/**/
	void PlaySkill_Q();
	void PlaySkill_W();
	void PlaySkill_E();
	void PlaySkill_R();

	/* 현재 무기 상태 바꿈 -> CharacterBase에서 실행 */
	void SetWeaponType(const int32& InCurrentWeaponType);

private:
	//Sword Skill Montage
	void BeginSwordSting();	//검 Q - 찌르기 시작
	void EndSwordSting(class UAnimMontage* Target, bool IsProperlyEnded);	//검 Q - 찌르기 끝
	void BeginSwordWhirlwind(); //검 W - 휠윈드 시작
	void EndSwordWhirlwind(class UAnimMontage* Target, bool IsProperlyEnded); //검 W - 휠윈드 끝
	void BeginSwordParrying(); //검 E - 패링 시작
	void EndSwordParrying(class UAnimMontage* Target, bool IsProperlyEnded); //검 E - 패링 끝
	void BeginSwordAura(); //검 R - 검기 시작
	void EndSwordAura(class UAnimMontage* Target, bool IsProperlyEnded); //검 R - 검기 끝

	//Bow Skill Montage
	void BeginBowSeveralArrows();
	void EndBowSeveralArrows(class UAnimMontage* Target, bool IsProperlyEnded);
	void BeginBowExplosionArrow();
	void EndBowExplosionArrow(class UAnimMontage* Target, bool IsProperlyEnded);
	void BeginBowBackstep();
	void EndBowBackstep(class UAnimMontage* Target, bool IsProperlyEnded);
	void BeginBowOneShot();
	void EndBowOneShot(class UAnimMontage* Target, bool IsProperlyEnded);
	void FireOneShot();

	virtual void Bow_Q_Skill() override; //활 Q 화살 소환 로직
	virtual void Bow_W_Skill() override; //활 W 애니메이션 중간에 멈추기


	//Staff Skill Montage
	void BeginStaffMeteor(); //스태프 Q - 메테오 시작
	void EndStaffMeteor(class UAnimMontage* Target, bool IsProperlyEnded); //스태프 Q - 메테오 끝
	void BeginStaffArea(); //스태프 W - 범위 바인딩 시작
	void EndStaffArea(class UAnimMontage* Target, bool IsProperlyEnded); //스태프 W - 범위 바인딩 끝
	void BeginStaffUpGround(); //스태프 E - 범위 지각 변동 시작
	void EndStaffUpGround(class UAnimMontage* Target, bool IsProperlyEnded); //스태프 E - 범위 지각 변동 끝
	void BeginStaffThunderbolt(); //스태프 R - 주위 번개 공격 시작
	void EndStaffThunderbolt(class UAnimMontage* Target, bool IsProperlyEnded); //스태프 R - 주위 번개 공격 끝

	/* 스킬 몽타주 모아놓은 Primary Asset */
	UPROPERTY(EditAnywhere, Category = "Montage")
	TObjectPtr<class UCharacterSkillMontageData> SkillMontageData;

	/* 스킬 시전할 곳 표시 하기 위한 데이터 */
	FHitResult Cursor;
	bool bCasting = false;

public:
	//현재 캐스팅되는 스킬을 담을 컨테이너
	TQueue<TFunction<void()>> SkillQueue;

/* Bow 데이터 */
private:
	UPROPERTY(EditAnywhere, Category = "Bow")
	TObjectPtr<class UParticleSystem> RainArrows;

	UPROPERTY(EditAnywhere, Category = "Bow")
	TSubclassOf<class AArrow> ArrowClass;

	FTimerHandle AutoTargetingTimer;

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

	bool bCanChangeWeapon = true;
	int32 CurrentWeaponType = 0;
	
};
