// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Stat/StatBase.h"
#include "EnemyStatComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CAPSTONEPROJECT_API UEnemyStatComponent : public UStatBase
{
	GENERATED_BODY()

public:	
	UEnemyStatComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	FORCEINLINE float GetCurrentHp() const { return CurrentHp; }
	FORCEINLINE float GetCurrentMp() const { return CurrentMp; }
	FORCEINLINE float GetCurrentDamage() const { return CurrentDamage; }
	FORCEINLINE float GetCurrentRange() const { return CurrentRange; }
	FORCEINLINE float GetCurrentMoveSpeed() const { return CurrentMoveSpeed; }

	float ApplyDamage(float InDamage);
	void SetHp(float ChangeHp);

private:
	UPROPERTY(VisibleAnywhere, Category = "Stat")
	TObjectPtr<class UEnemyDataStat> DataStat;

	UPROPERTY(EditAnywhere, Category = "Stat")
	float CurrentHp;

	UPROPERTY(EditAnywhere, Category = "Stat")
	float CurrentMp;

	UPROPERTY(EditAnywhere, Category = "Stat")
	float CurrentDamage;

	UPROPERTY(EditAnywhere, Category = "Stat")
	float CurrentRange;

	UPROPERTY(EditAnywhere, Category = "Stat")
	float CurrentMoveSpeed;
		
};
