// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Ranged/BTTask_FindToLocation.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interface/AIInterface.h"
#include "NavigationSystem.h"

UBTTask_FindToLocation::UBTTask_FindToLocation()
{
	NodeName = TEXT("FindToLocation");
}

EBTNodeResult::Type UBTTask_FindToLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type SuperResult = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* PossessedPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (PossessedPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	APawn* TargetPawn = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));
	if (TargetPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	IAIInterface* Interface = Cast<IAIInterface>(PossessedPawn);
	if (Interface == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(PossessedPawn->GetWorld());
	if (NavSystem == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	float Radius = Interface->GetPatrolRadius();

	//뒷걸음질을 구현하고 싶은데 마음처럼 안되네
	FVector Origin = PossessedPawn->GetActorLocation();
	FVector Target = TargetPawn->GetActorLocation();
	FVector BackwardDirection = (Target - Origin).GetSafeNormal();
	
	Cast<AAIController>(PossessedPawn->GetController())->MoveToLocation(-(Origin + BackwardDirection * 420.f));

	return EBTNodeResult::Succeeded;
}
