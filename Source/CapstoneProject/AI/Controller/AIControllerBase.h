// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIControllerBase.generated.h"

UENUM()
enum class EAIPerceptionSense : uint8
{
	EPS_None = 0,
	EPS_Sight,
	EPS_Damage
};
/**
 * 
 */
UCLASS()
class CAPSTONEPROJECT_API AAIControllerBase : public AAIController
{
	GENERATED_BODY()

public:
	AAIControllerBase();

	void RunAI();
	void StopAI();

protected:
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(EditAnywhere, Category = "BB")
	TObjectPtr<class UBlackboardData> BBData;
	
	UPROPERTY(EditAnywhere, Category = "BT")
	TObjectPtr<class UBehaviorTree> BTData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAIPerceptionComponent> AIPerception;
};
