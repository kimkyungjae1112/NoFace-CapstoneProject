// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerHpBarUserWidget.h"
#include "PlayerExpBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROJECT_API UPlayerExpBarWidget : public UPlayerHpBarUserWidget
{
	GENERATED_BODY()
	
public:
	UPlayerExpBarWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	void UpdateExpBar(float NewCurrentExp);
protected:
	UPROPERTY(VisibleAnywhere, Category = "ExpBar")
	TObjectPtr<class UProgressBar> ExpProgressBar;

};

