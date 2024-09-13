// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterSkillMontageData.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROJECT_API UCharacterSkillMontageData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "Sword")
	TArray<class UAnimMontage*> SwordMontages;

	UPROPERTY(EditAnywhere, Category = "Bow")
	TArray<class UAnimMontage*> BowMontages;

	UPROPERTY(EditAnywhere, Category = "Staff")
	TArray<class UAnimMontage*> StaffMontages;

};
