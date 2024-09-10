// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WeaponChoiceUI.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROJECT_API UWeaponChoiceUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UWeaponChoiceUI(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnClickButtonSword();

	UFUNCTION()
	void OnClickButtonBow();

	UFUNCTION()
	void OnClickButtonStaff();


private:
	UPROPERTY()
	TObjectPtr<class UButton> SwordButtonPtr;
	
	UPROPERTY()
	TObjectPtr<class UButton> BowButtonPtr;

	UPROPERTY()
	TObjectPtr<class UButton> StaffButtonPtr;


};
