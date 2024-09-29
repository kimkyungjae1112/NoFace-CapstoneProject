// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/EnemyPtrWidget.h"
#include "EnemyHpBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROJECT_API UEnemyHpBarWidget : public UEnemyPtrWidget
{
	GENERATED_BODY()
	
public:
	UEnemyHpBarWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	void UpdateHpBar(float NewHp);
	void SetMaxHp(float InMaxHp);

private:
	UPROPERTY(VisibleAnywhere, Category = "HpBar")
	TObjectPtr<class UProgressBar> HpBar;

	float MaxHp;
};
