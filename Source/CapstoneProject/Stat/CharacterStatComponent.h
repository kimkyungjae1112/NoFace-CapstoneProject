// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Stat/StatBase.h"
#include "CharacterStatComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CAPSTONEPROJECT_API UCharacterStatComponent : public UStatBase
{
	GENERATED_BODY()

public:	
	UCharacterStatComponent();

protected:
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	FORCEINLINE float GetMaxHp() const { return MaxHp; }
	FORCEINLINE float GetCurrentHp() const { return CurrentHp; }
	FORCEINLINE float GetCurrentExp() const { return CurrentExp; }
	FORCEINLINE void SetCurrentExp(float InExp) { CurrentExp = InExp; }
	FORCEINLINE float GetCurrentLevel() const { return CurrentExp; }
	FORCEINLINE void SetCurrentLevel(float InLevel) { CurrentLevel = InLevel; }

	float ApplyDamage(float InDamage);
	void SetHp(float ChangeHp);

private:
	void SetExp(float InExp);

private:
	UPROPERTY(VisibleAnywhere, Category = "Stat")
	TObjectPtr<class UCharacterDataStat> DataStat;

	UPROPERTY(EditAnywhere, Category = "Stat")
	float MaxHp;

	UPROPERTY(EditAnywhere, Category = "Stat")
	float CurrentHp;

	UPROPERTY(EditAnywhere, Category = "Stat")
	float CurrentExp;

	UPROPERTY(EditAnywhere, Category = "Stat")
	int32 CurrentLevel;


};
