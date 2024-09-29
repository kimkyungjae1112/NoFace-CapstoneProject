// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "EnemyHpBarWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROJECT_API UEnemyHpBarWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
protected:
	virtual void InitWidget() override;
};
