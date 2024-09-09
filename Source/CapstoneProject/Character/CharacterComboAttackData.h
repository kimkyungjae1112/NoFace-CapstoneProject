// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterComboAttackData.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROJECT_API UCharacterComboAttackData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "Name")
	FString MontageSectionNamePrefix;

	UPROPERTY(EditAnywhere, Category = "Count")
	uint8 MaxComboCount;

	UPROPERTY(EditAnywhere, Category = "Rate")
	float FrameRate;

	UPROPERTY(EditAnywhere, Category = "ComboData")
	TArray<float> EffectiveFrameCount;
};
