// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Ranged/BTService_RangedAttackInRange.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interface/AIInterface.h"

UBTService_RangedAttackInRange::UBTService_RangedAttackInRange()
{
	NodeName = TEXT("Ranged Attack In Range");
	Interval = 1.f;
}

void UBTService_RangedAttackInRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* PossessedPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (PossessedPawn == nullptr)
	{
		return;
	}

	APawn* Target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));
	if (Target == nullptr)
	{
		return;
	}

	IAIInterface* Interface = Cast<IAIInterface>(PossessedPawn);
	if (Interface == nullptr)
	{
		return;
	}

	float Distance = FVector::Distance(PossessedPawn->GetActorLocation(), Target->GetActorLocation());
	if (Distance <= Interface->GetAttackInRange())
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("CanAttack"), true);
		if (Distance <= 500.f)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("CanBackstep"), true);
			UE_LOG(LogTemp, Display, TEXT("Can Backstep"));
		}
		else
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("CanBackstep"), false);
			UE_LOG(LogTemp, Display, TEXT("No Backstep"));
		}
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("CanAttack"), false);
	}
}
