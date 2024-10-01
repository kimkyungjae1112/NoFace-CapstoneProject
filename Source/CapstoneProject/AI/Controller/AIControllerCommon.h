// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Controller/AIControllerBase.h"
#include "AIControllerCommon.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROJECT_API AAIControllerCommon : public AAIControllerBase
{
	GENERATED_BODY()

public:
	AAIControllerCommon();

public:
	UFUNCTION()
	void PerceptionUpdated(const TArray<AActor*>& UpdatedActors);

	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAIPerceptionComponent> AIPerception;

	TObjectPtr<class UAISenseConfig_Sight> SightConfig;
};
