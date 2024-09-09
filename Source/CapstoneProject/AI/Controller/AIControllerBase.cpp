// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Controller/AIControllerBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTree.h"

AAIControllerBase::AAIControllerBase()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBDataRef(TEXT(""));
	if (BBDataRef.Object)
	{
		BBData = BBDataRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTDataRef(TEXT(""));
	if (BTDataRef.Object)
	{
		BTData = BTDataRef.Object;
	}

}

void AAIControllerBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AAIControllerBase::RunAI()
{
}

void AAIControllerBase::StopAI()
{
}
