// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UI/PlayerHpBarWidget.h"
#include "PlayerHpBarWidgetInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPlayerHpBarWidgetInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CAPSTONEPROJECT_API IPlayerHpBarWidgetInterface
{
	GENERATED_BODY()

public:
	virtual void SetupPlayerHpBarWidget(class UPlayerHpBarWidget* InPlayerHpBarWidget) = 0;
};
