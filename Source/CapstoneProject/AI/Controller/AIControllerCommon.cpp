// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Controller/AIControllerCommon.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

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

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->SightRadius = 800.f;
	SightConfig->LoseSightRadius = 1200.f;
	SightConfig->PeripheralVisionAngleDegrees = 60.f;
	SightConfig->SetMaxAge(5.f);
	SightConfig->AutoSuccessRangeFromLastSeenLocation = -1.f;

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

	AIPerception->ConfigureSense(*SightConfig);
	AIPerception->SetDominantSense(SightConfig->GetSenseImplementation());

	//AIPerception->OnPerceptionUpdated.AddDynamic(this, &AAIControllerCommon::PerceptionUpdated);
	AIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &AAIControllerCommon::OnPerceptionUpdated);
}

void AAIControllerCommon::PerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	
}

void AAIControllerCommon::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	FActorPerceptionBlueprintInfo ActorPerceptionBlueprintIntfo;
	AIPerception->GetActorsPerception(Actor, ActorPerceptionBlueprintIntfo);
	
	if (Stimulus.WasSuccessfullySensed())
	{
		// Actor 감지됨
		GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), Actor);
		UE_LOG(LogTemp, Display, TEXT("Target detected at location: %s"), *Stimulus.StimulusLocation.ToString());
		UE_LOG(LogTemp, Log, TEXT("Target detected: %s"), *Actor->GetName());

		// 자극의 유형 출력 (어떤 감각을 통해 자극이 감지되었는지)
		UE_LOG(LogTemp, Log, TEXT("Stimulus Type: %s"), *Stimulus.Type.Name.ToString());
	}
	else
	{
		// Actor 감지 안됨
		GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), nullptr);
		UE_LOG(LogTemp, Log, TEXT("Target lost: %s"), *Actor->GetName());
	}
	
}
