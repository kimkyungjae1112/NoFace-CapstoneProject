// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Stat/CharacterDataStat.h"
#include "HUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROJECT_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UHUDWidget(const FObjectInitializer& OnjectInitializer);

public:
	void UpdateHpBar(float NewCurrentHp);
	void UpdateExpBar(float NewCurrentExp);
	void SetMaxHp(float NewMaxHp);

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY()
	TObjectPtr<class UPlayerHpBarWidget> HpBar;

	UPROPERTY()
	TObjectPtr<class UPlayerExpBarWidget> ExpBar;

};
