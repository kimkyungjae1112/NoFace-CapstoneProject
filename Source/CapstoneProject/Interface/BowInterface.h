// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BowInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBowInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CAPSTONEPROJECT_API IBowInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void SetBow(class ABow* InBow) = 0;
	virtual void StartAnimation() = 0;
	virtual void EndAnimation() = 0;
	virtual void SwordDefaultAttackEnd() = 0;
};
