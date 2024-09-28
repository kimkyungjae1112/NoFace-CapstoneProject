// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EnemyDataStat.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROJECT_API UEnemyDataStat : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hp")
	float Hp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mp")
	float Mp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float Range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float MoveSpeed;

};
