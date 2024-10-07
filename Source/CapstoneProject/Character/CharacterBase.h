// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Interface/PlayerHUDInterface.h"
#include "CharacterBase.generated.h"

//Animation Blueprint 에서 무기 애니메이션 값을 바꿀 때 쓰는 ENUM 값
UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Sword = 0 UMETA(DisplayName = "Sword"),
	Bow UMETA(DisplayName = "Bow"),
	Staff UMETA(DisplayName = "Staff")
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
class CAPSTONEPROJECT_API ACharacterBase : public ACharacter, public IPlayerHUDInterface
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
	virtual void SetupHUDWidget(class UHUDWidget* InHUDWidget) override;

/* Getter */

public:

	UFUNCTION(BlueprintCallable, Category = "WeaponType")
	int GetWeaponType();

/* 스킬 섹션 */
protected:
	void Q_Skill();
	void W_Skill();
	void E_Skill();
	void R_Skill();


/* 카메라 섹션 */
protected:
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<class USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<class UCameraComponent> Camera;


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
	TObjectPtr<class UInputAction> NextWeaponAction; 
	
	UPROPERTY(VisibleAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> PrevWeaponAction; 
	
	UPROPERTY(VisibleAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> CancelAction;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> ZoomInOutAction;

/* 마우스 우클릭을 통해 캐릭터 이동 기능을 실현하는 함수와 변수 */
	void OnClickStart();	//Mouse Right Click Started
	void OnClicking();	//Mouse Right Click Triggered
	void OnRelease();	//Mouse Right Click Completed

	FVector CachedLocation;


/* 마우스 좌클릭을 이용한 콤보공격 구현 */
	void OnAttackStart();
	bool TraceAttack();
	
	FHitResult AttackHitResult;	//공격하는 방향을 알기 위한 변수

	UPROPERTY(VisibleAnywhere, Category = "Component")
	TObjectPtr<class UCharacterDefaultAttackComponent> AttackComponent;

/* 마우스 휠을 이용한 줌 인아웃 */
	void ZoomInOut(const FInputActionValue& Value);

/* 캐스팅 스킬 */
	void CancelCasting();


/* 무기 교체 */
	void NextWeapon();
	void PrevWeapon();
	void AnimWeaponIndex();
	void ChangeWeapon();

	void EquipSword();	//무기 장착할 때 호출되는 함수
	void EquipBow();	//무기 장착할 때 호출되는 함수
	void EquipStaff();	//무기 장착할 때 호출되는 함수

	UPROPERTY(EditAnywhere, Category = "Weapon")
	EWeaponType CurrentWeaponType;

	UPROPERTY()
	TArray<FTakeItemDelegateWrapper> TakeItemDelegateArray;

	int32 WeaponIndex = 0;	//무기 인덱스
	
/* 중복 입력 방지, 구현 보류 */
	void StopInput();

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


/* 스킬 섹션 */
private:
	UPROPERTY(EditAnywhere, Category = "Component")
	TObjectPtr<class USkillComponent> SkillComponent;

	UPROPERTY(EditAnywhere, Category = "Component")
	TObjectPtr<class UCharacterHitCheckComponent> HitCheckComponent;

	//패링을 위한 함수와 변수
	void ToggleParrying();
	bool bIsParrying = false;

/* 스텟 섹션 */
private:
	UPROPERTY(VisibleAnywhere, Category = "Component")
	TObjectPtr<class UCharacterStatComponent> Stat;

/* 유틸리티 섹션 */
private:
	class ACPlayerController* GetPlayerController() const;

	void RotateToTarget();	//캐릭터 회전을 도와줌
	void UpdateRotate();
	FTimerHandle RotateTimer;

};
