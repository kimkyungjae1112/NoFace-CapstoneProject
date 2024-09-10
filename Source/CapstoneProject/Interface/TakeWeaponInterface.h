// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TakeWeaponInterface.generated.h"

UENUM()
enum class EWeaponType : uint8
{
	Sword = 0,
	Bow,
	Staff
};

UINTERFACE(MinimalAPI)
class UTakeWeaponInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CAPSTONEPROJECT_API ITakeWeaponInterface
{
	GENERATED_BODY()

public:
	virtual void TakeWeapon(EWeaponType WeaponType) = 0;
	virtual void CloseWeaponChoiceUI() = 0;
};
