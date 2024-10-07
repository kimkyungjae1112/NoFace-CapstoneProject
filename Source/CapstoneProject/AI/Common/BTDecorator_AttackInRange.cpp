// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Common/BTDecorator_AttackInRange.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interface/AIInterface.h"

UBTDecorator_AttackInRange::UBTDecorator_AttackInRange()
{
	NodeName = TEXT("AttackInRange");
	bNotifyTick = true;
}

bool UBTDecorator_AttackInRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool SuperResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	APawn* PossessedPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (PossessedPawn == nullptr)
	{
		return false;
	}

	APawn* Target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));
	if (Target == nullptr)
	{
		return false;
	}

	IAIInterface* Interface = Cast<IAIInterface>(PossessedPawn);
	if (Interface == nullptr)
	{
		return false;
	}

	float Distance = FVector::Distance(PossessedPawn->GetActorLocation(), Target->GetActorLocation());
	DrawDebugSphere(GetWorld(), PossessedPawn->GetActorLocation(), Interface->GetAttackInRange(), 12, FColor::Green, false, 3.f);

	return Distance <= Interface->GetAttackInRange();
}
