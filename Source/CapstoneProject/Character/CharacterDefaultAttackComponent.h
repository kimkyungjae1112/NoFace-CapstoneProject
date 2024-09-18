// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterDefaultAttackComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CAPSTONEPROJECT_API UCharacterDefaultAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCharacterDefaultAttackComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


public:
	void BeginAttack();

private:
	void BeginDefaultAttack();
	void EndDefaultAttack(class UAnimMontage* Target, bool IsProperlyEnded);
	void SetComboTimer();
	void CheckCombo();

private:
	FTimerHandle ComboTimer;
	int32 CurrentCombo = 0;
	bool HasNextComboCommand = false;

	UPROPERTY(EditAnywhere, Category = "Combo")
	TObjectPtr<class UCharacterComboAttackData> ComboData;

	UPROPERTY(EditAnywhere, Category = "Montage")
	TObjectPtr<class UAnimMontage> DefaultAttackMontage;

private:
	UPROPERTY(VisibleAnywhere, Category = "Character")
	TObjectPtr<class ACharacter> Character;

};
