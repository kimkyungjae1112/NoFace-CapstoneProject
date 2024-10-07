// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FindToLocation.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROJECT_API UBTTask_FindToLocation : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_FindToLocation();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
