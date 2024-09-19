// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterDefaultAttackComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CAPSTONEPROJECT_API UCharacterDefaultAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCharacterDefaultAttackComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void SetWeaponType(const int32& InCurrentWeaponType);

	void BeginAttack();

/* Sword 기본 공격 */
private:
	void BeginSwordDefaultAttack();
	void EndSwordDefaultAttack(class UAnimMontage* Target, bool IsProperlyEnded);
	void SetSwordComboTimer();
	void CheckSwordCombo();

	FTimerHandle SwordComboTimer;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TObjectPtr<class UCharacterComboAttackData> SwordComboData;

	UPROPERTY(EditAnywhere, Category = "Montage")
	TObjectPtr<class UAnimMontage> SwordDefaultAttackMontage;

/* Bow 기본 공격 */
private:
	void BeginBowDefaultAttack();
	void EndBowDefaultAttack(class UAnimMontage* Target, bool IsProperlyEnded);
	void SetBowComboTimer();
	void CheckBowCombo();

	FTimerHandle BowComboTimer;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TObjectPtr<class UCharacterComboAttackData> BowComboData;

	UPROPERTY(EditAnywhere, Category = "Montage")
	TObjectPtr<class UAnimMontage> BowDefaultAttackMontage;

/* Bow 기본 공격 */
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

	UPROPERTY(VisibleAnywhere, Category = "Character")
	TObjectPtr<class ACharacter> Character;

};
