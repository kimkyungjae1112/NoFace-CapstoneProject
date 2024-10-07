// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROJECT_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UEnemyAnimInstance();

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere, Category = "Character")
	TObjectPtr<class ACharacter> Character;

	UPROPERTY(VisibleAnywhere, Category = "Character")
	TObjectPtr<class UCharacterMovementComponent> Movement;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Var")
	uint8 bIsIdle : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Var")
	uint8 bIsBattle : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Var")
	float GroundSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Var")
	float MovingThreshould;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Var")
	FVector Velocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Var")
	FVector Angle;

};
