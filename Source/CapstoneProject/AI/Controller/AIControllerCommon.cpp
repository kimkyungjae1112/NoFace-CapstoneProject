// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Controller/AIControllerCommon.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTree.h"

AAIControllerCommon::AAIControllerCommon()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBDataRef(TEXT("/Script/AIModule.BlackboardData'/Game/No-Face/AI/Melee/BB_MeleeCommon.BB_MeleeCommon'"));
	if (BBDataRef.Object)
	{
		BBData = BBDataRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTDataRef(TEXT("/Script/AIModule.BehaviorTree'/Game/No-Face/AI/Melee/BT_MeleeCommon.BT_MeleeCommon'"));
	if (BTDataRef.Object)
	{
		BTData = BTDataRef.Object;
	}
}
