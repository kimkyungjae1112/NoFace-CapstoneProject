// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterDataStat.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROJECT_API UCharacterDataStat : public UPrimaryDataAsset
{
	GENERATED_BODY()

/* 일반 스텟 */
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common")
	float MaxHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common")
	float Hp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common")
	float Exp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common")
	int32 Level;

/* 검 스텟 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sword")
	float SwordDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sword")
	float SwordRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sword")
	float SwordDegree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sword")
	float Sword_Q_Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sword")
	float Sword_Q_Range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sword")
	float Sword_W_Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sword")
	float Sword_W_Range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sword")
	float Sword_R_Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sword")
	float Sword_R_MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sword")
	float Sword_R_LifeTime;

/* 활 스텟 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bow")
	float BowDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bow")
	float BowSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bow")
	float BowLifeTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bow")
	float Bow_Q_Degree;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bow")
	float Bow_Q_Amount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bow")
	float Bow_W_Damage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bow")
	float Bow_E_Distance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bow")
	float Bow_R_Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bow")
	float Bow_R_Range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bow")
	FVector Bow_R_BoxExtent;

/* 스태프 스텟 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Staff")
	float StaffDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Staff")
	float Staff_Q_Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Staff")
	float Staff_W_Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Staff")
	float Staff_W_LifeTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Staff")
	float Staff_E_Damage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Staff")
	float Staff_R_Damage;

};

