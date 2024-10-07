// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHpBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROJECT_API UPlayerHpBarWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:
	UPlayerHpBarWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	void SetMaxHp(float NewMaxHp);
	void UpdateHpBar(float NewCurrentHp);

protected:
	UPROPERTY(VisibleAnywhere, Category = "HpBar")
	TObjectPtr<class UProgressBar> HpProgressBar;

	UPROPERTY()
	float MaxHp;

	
};
