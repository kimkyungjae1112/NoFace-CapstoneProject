// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Controller/AIControllerTanker.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTree.h"

AAIControllerTanker::AAIControllerTanker()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBDataRef(TEXT("/Script/AIModule.BlackboardData'/Game/No-Face/AI/Melee/BB_MeleeTanker.BB_MeleeTanker'"));
	if (BBDataRef.Object)
	{
		BBData = BBDataRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTDataRef(TEXT("/Script/AIModule.BehaviorTree'/Game/No-Face/AI/Melee/BT_MeleeTanker.BT_MeleeTanker'"));
	if (BTDataRef.Object)
	{
		BTData = BTDataRef.Object;
	}
}


