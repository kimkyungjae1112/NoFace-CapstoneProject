// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

UENUM(BlueprintType)
enum class EQSkillType : uint8
{
	Charge = 0,
	Double
};

UENUM(BlueprintType)
enum class EWSkillType : uint8
{
	UnConfirmed = 0
};

UENUM(BlueprintType)
enum class EESkillType : uint8
{
	UnConfirmed = 0
};

UENUM(BlueprintType)
enum class ERSkillType : uint8
{
	UnConfirmed = 0
};

DECLARE_DELEGATE(FTakeItemDelegate)

USTRUCT()
struct FTakeItemDelegateWrapper
{
	GENERATED_BODY()

	FTakeItemDelegateWrapper() {}
	FTakeItemDelegateWrapper(const FTakeItemDelegate& InTakeItemDelegate) : TakeItemDelegate(InTakeItemDelegate) {}

	FTakeItemDelegate TakeItemDelegate;
};

UCLASS()
class CAPSTONEPROJECT_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ACharacterBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

/* 오버라이딩 섹션 */
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

/* 스킬 섹션 */
protected:
	virtual void Q_Skill();
	virtual void W_Skill();
	virtual void E_Skill();
	virtual void R_Skill();


/* 카메라 섹션 */
protected:
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<class USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<class UCameraComponent> Camera;

/* 스킬 섹션 */
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill", meta = (AllowPrivateAccess = "true"))
	EQSkillType CurrentQSkillType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill", meta = (AllowPrivateAccess = "true"))
	EWSkillType CurrentWSkillType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill", meta = (AllowPrivateAccess = "true"))
	EESkillType CurrentESkillType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill", meta = (AllowPrivateAccess = "true"))
	ERSkillType CurrentRSkillType;

	
	TMap<EQSkillType, class USkill_Q_Base*> Q_SkillMap;
	TMap<EWSkillType, class USkill_W_Base*> W_SkillMap;
	TMap<EESkillType, class USkill_E_Base*> E_SkillMap;
	TMap<ERSkillType, class USkill_R_Base*> R_SkillMap;


/* Enhanced Input */
private:
	UPROPERTY(VisibleAnywhere, Category = "Input")
	TObjectPtr<class UInputMappingContext> InputMappingContext;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> RightClickAction;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> Q_SkillAction;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> W_SkillAction;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> E_SkillAction;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> R_SkillAction;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> LeftClickAction;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> NextWeaponAction; // X키
	
	UPROPERTY(VisibleAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> PrevWeaponAction; // Z키

/* 마우스 우클릭을 통해 캐릭터 이동 기능을 실현하는 함수와 변수 */
	void OnClickStart();	//Mouse Right Click Started
	void OnClicking();	//Mouse Right Click Triggered
	void OnRelease();	//Mouse Right Click Completed

	FVector CachedLocation;

/* 마우스 좌클릭을 이용한 콤보공격 구현 */
	void OnAttackStart();
	bool TraceAttack();
	void BeginDefaultAttack();
	void EndDefaultAttack(class UAnimMontage* Target, bool IsProperlyEnded);
	void SetComboTimer();
	void CheckCombo();
	void RotateToTarget();
	void UpdateRotate();

	FTimerHandle ComboTimer;
	FTimerHandle RotateTimer;
	int32 CurrentCombo = 0;
	bool HasNextComboCommand = false;
	FHitResult AttackHitResult;

	UPROPERTY(EditAnywhere, Category = "Combo")
	TObjectPtr<class UCharacterComboAttackData> ComboData;

	UPROPERTY(EditAnywhere, Category = "Montage")
	TObjectPtr<class UAnimMontage> DefaultAttackMontage;

/* 무기 교체 */
	void NextWeapon();
	void PrevWeapon();

	void EquipSword();
	void EquipBow();
	void EquipStaff();

	UPROPERTY()
	TArray<FTakeItemDelegateWrapper> TakeItemDelegateArray;

	int32 WeaponIndex = 0;
	
/* 무기 데이터 섹션 */
private:
	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<class ASword> SwordClass;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<class ABow> BowClass;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<class AStaff> StaffClass;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	TObjectPtr<class AWeaponBase> WeaponBase;


/* 스텟 섹션 */
private:
	UPROPERTY(VisibleAnywhere, Category = "Stat")
	TObjectPtr<class UCharacterStatComponent> Stat;


/* 유틸리티 섹션 */
private:
	class ACPlayerController* GetPlayerController() const;
};
