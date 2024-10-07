// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "PlayerExpBarWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROJECT_API UPlayerExpBarWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
protected:
	virtual void InitWidget() override;
};
