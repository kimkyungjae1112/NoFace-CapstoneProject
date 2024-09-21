// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/StaffArea.h"
#include "Engine/OverlapResult.h"
#include "Engine/DamageEvents.h"

AStaffArea::AStaffArea()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Area = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Area->SetupAttachment(Root);
	Area->SetCollisionProfileName(TEXT("NoCollision"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> AreaRef(TEXT("/Script/Engine.StaticMesh'/Game/ParagonGideon/FX/Meshes/Heroes/Gideon/SM_BigPortal_Space.SM_BigPortal_Space'"));
	if (AreaRef.Object)
	{
		Area->SetStaticMesh(AreaRef.Object);
	}
}

void AStaffArea::BeginPlay()
{
	Super::BeginPlay();
	
}

void AStaffArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//CheckInArea를 해
		//true면
		//PullToCenter를 호출해서 몬스터를 중앙으로 모으고 대미지를 줘
}

bool AStaffArea::CheckInArea()
{
	const float Radius = 100.f;

	FVector Origin = GetActorLocation();
	FCollisionQueryParams Params(NAME_None, true, GetOwner()); //GetOwner 꼭 설정해주기
	TArray<FOverlapResult> OverlapResults;

	return GetWorld()->OverlapMultiByChannel(OverlapResults, Origin, FQuat::Identity, ECC_GameTraceChannel2, FCollisionShape::MakeSphere(Radius), Params);
}

void AStaffArea::PullToCenter()
{
}

