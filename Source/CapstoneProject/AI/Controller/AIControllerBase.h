// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIControllerBase.generated.h"

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

	UPROPERTY(VisibleAnywhere, Category = "BT")
	TObjectPtr<class UBlackboardData> BBData;
	
	UPROPERTY(VisibleAnywhere, Category = "BT")
	TObjectPtr<class UBehaviorTree> BTData;
};
