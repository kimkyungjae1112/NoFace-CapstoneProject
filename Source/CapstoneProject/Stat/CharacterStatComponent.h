// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHpZero);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHpChanged, float /* CurrentHp */);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CAPSTONEPROJECT_API UCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCharacterStatComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FORCEINLINE float GetCurrentHp() const { return CurrentHp; }
	FORCEINLINE float GetCurrentMp() const { return CurrentMp; }
	FORCEINLINE float GetCurrentDamage() const { return CurrentDamage; }

	FOnHpZero OnHpZero;
	FOnHpChanged OnHpChanged;

	float ApplyDamage(float InDamage);
	void SetHp(float ChangeHp);

private:
	UPROPERTY(VisibleAnywhere, Category = "Stat")
	TObjectPtr<class UCharacterDataStat> DataStat;

	float CurrentHp;
	float CurrentMp;
	float CurrentDamage;
};
