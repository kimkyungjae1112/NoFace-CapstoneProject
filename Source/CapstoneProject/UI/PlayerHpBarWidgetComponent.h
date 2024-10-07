// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "PlayerHpBarWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROJECT_API UPlayerHpBarWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

protected:
	virtual void InitWidget() override;
	
};
