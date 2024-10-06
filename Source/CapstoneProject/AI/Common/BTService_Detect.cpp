// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Common/BTService_Detect.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interface/AIInterface.h"
#include "Engine/OverlapResult.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.f;
	DetectTime = 0.f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* PossessedPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (PossessedPawn == nullptr)
	{
		return;
	}

	UWorld* World = PossessedPawn->GetWorld();
	if (World == nullptr)
	{
		return;
	}

	IAIInterface* Interface = Cast<IAIInterface>(PossessedPawn);
	if (Interface == nullptr)
	{
		return;
	}

	float Radius = Interface->GetDetectRadius();
	FVector Origin = PossessedPawn->GetActorLocation();
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams Params(NAME_None, false, PossessedPawn);
	
	bool bOverlap = World->OverlapMultiByChannel(OverlapResults, Origin, FQuat::Identity, ECC_GameTraceChannel1, FCollisionShape::MakeSphere(Radius), Params);
	if (bOverlap)
	{
		for (auto const& OverlapResult : OverlapResults)
		{
			APawn* Target = Cast<APawn>(OverlapResult.GetActor());

			/* 몬스터의 일정범위 안으로 들어가면 DetectTime이 쌓이고 설정된 DetectTime을 넘어가면 몬스터가 플레이어를 인지 */
			DetectTime += DeltaSeconds;
			OwnerComp.GetBlackboardComponent()->SetValueAsFloat(TEXT("DetectTime"), DetectTime);
			return;
		}
	}
	DetectTime = 0.f;
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(TEXT("DetectTime"), DetectTime);
}
