// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Controller/AIControllerBase.h"
#include "AIControllerRifle.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROJECT_API AAIControllerRifle : public AAIControllerBase
{
	GENERATED_BODY()
	
public:
	AAIControllerRifle();

public:
	UFUNCTION()
	void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

/* Perception Sense 섹션 */
private:
	FAIStimulus CanSenseActor(AActor* Actor, EAIPerceptionSense AIPerceptionSense);

	void HandleSenseSight(AActor* Actor, const FAIStimulus& AIStimulus);

private:
	TObjectPtr<class UAISenseConfig_Sight> SightConfig;

};
