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

	LifeTime = 5.f;
}

void AStaffArea::BeginPlay()
{
	Super::BeginPlay();
	
}

void AStaffArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CheckInArea())
	{
		PullToCenter(DeltaTime);
	}

	LifeTime -= DeltaTime;
	if (LifeTime <= 0.f)
	{
		Destroy();
	}
}

bool AStaffArea::CheckInArea()
{
	const float Radius = 200.f;

	FVector Origin = GetActorLocation();
	FCollisionQueryParams Params(NAME_None, true, GetOwner()); //GetOwner 꼭 설정해주기
	DrawDebugSphere(GetWorld(), Origin, Radius, 32, FColor::Red, false);

	return GetWorld()->OverlapMultiByChannel(OverlapResults, Origin, FQuat::Identity, ECC_GameTraceChannel2, FCollisionShape::MakeSphere(Radius), Params);
}

void AStaffArea::PullToCenter(float DeltaTime)
{
	for (const auto& OverlapResult : OverlapResults)
	{
		FVector Target = GetActorLocation();
		AActor* Actor = OverlapResult.GetActor();
		Actor->SetActorLocation(FMath::VInterpTo(Actor->GetActorLocation(), Target, DeltaTime, 0.25f));
	}
}
