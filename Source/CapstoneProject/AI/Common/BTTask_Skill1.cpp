// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Common/BTTask_Skill1.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interface/AIInterface.h"

UBTTask_Skill1::UBTTask_Skill1()
{
	NodeName = TEXT("Skill1");
}

EBTNodeResult::Type UBTTask_Skill1::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type SuperResult = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* PossessedPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (PossessedPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	IAIInterface* Interface = Cast<IAIInterface>(PossessedPawn);
	if (Interface == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	FEnemySkill1Finished EnemySkill1Finished;
	EnemySkill1Finished.BindLambda(
		[&]()
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsFloat(TEXT("SkillEnergy"), 0.f);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		});

	Interface->SetEnemySkill1Delegate(EnemySkill1Finished);
	Interface->Skill1ByAI();
		
	return EBTNodeResult::InProgress;
}
