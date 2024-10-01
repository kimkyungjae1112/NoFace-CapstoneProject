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

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FORCEINLINE float GetCurrentHp() const { return CurrentHp; }
	FORCEINLINE float GetCurrentExp() const { return CurrentExp; }

	float ApplyDamage(float InDamage);
	void SetHp(float ChangeHp);

private:
	UPROPERTY(VisibleAnywhere, Category = "Stat")
	TObjectPtr<class UCharacterDataStat> DataStat;

	UPROPERTY(EditAnywhere, Category = "Stat")
	float CurrentHp;

	UPROPERTY(EditAnywhere, Category = "Stat")
	float CurrentExp;
};
