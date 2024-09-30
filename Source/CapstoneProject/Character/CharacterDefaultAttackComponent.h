// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/BowInterface.h"
#include "CharacterDefaultAttackComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CAPSTONEPROJECT_API UCharacterDefaultAttackComponent : public UActorComponent, public IBowInterface
{
	GENERATED_BODY()

public:	
	UCharacterDefaultAttackComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	FORCEINLINE bool CanChangeWeapon() { return bCanChangeWeapon; }

	void SetWeaponType(const int32& InCurrentWeaponType);

	void BeginAttack();

/* Sword 기본 공격 */
private:
	void BeginSwordDefaultAttack();
	void EndSwordDefaultAttack(class UAnimMontage* Target, bool IsProperlyEnded);
	void SetSwordComboTimer();
	void CheckSwordCombo();
	virtual void SwordDefaultAttackEnd() override;

	FTimerHandle SwordComboTimer;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TObjectPtr<class UCharacterComboAttackData> SwordComboData;

	UPROPERTY(EditAnywhere, Category = "Montage")
	TObjectPtr<class UAnimMontage> SwordDefaultAttackMontage;

/* Bow 기본 공격 */
private:
	void BeginBowDefaultAttack();
	void EndBowDefaultAttack(class UAnimMontage* Target, bool IsProperlyEnded);
	virtual void SetBow(class ABow* InBow) override;
	virtual void StartAnimation() override;
	virtual void EndAnimation() override;

	UPROPERTY(EditAnywhere, Category = "Montage")
	TObjectPtr<class UAnimMontage> BowDefaultAttackMontage;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	TObjectPtr<class ABow> Bow;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<class AArrow> ArrowClass;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	TObjectPtr<class AArrow> Arrow;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TObjectPtr<class UAnimationAsset> BowPullAnim;
	
	
	UPROPERTY(EditAnywhere, Category = "Weapon")
	TObjectPtr<class UAnimationAsset> BowIdleAnim;


/* Staff 기본 공격 */
private:
	void BeginStaffDefaultAttack();
	void EndStaffDefaultAttack(class UAnimMontage* Target, bool IsProperlyEnded);
	void SetStaffComboTimer();
	void CheckStaffCombo();

	FTimerHandle StaffComboTimer;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TObjectPtr<class UCharacterComboAttackData> StaffComboData;

	UPROPERTY(EditAnywhere, Category = "Montage")
	TObjectPtr<class UAnimMontage> StaffDefaultAttackMontage;

/* 유틸리티 */
private:
	int32 CurrentCombo = 0;
	int32 CurrentWeaponType;
	bool HasNextComboCommand = false;

	bool bCanChangeWeapon = true;

	UPROPERTY(VisibleAnywhere, Category = "Character")
	TObjectPtr<class ACharacter> Character;

};
