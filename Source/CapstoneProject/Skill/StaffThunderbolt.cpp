// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/StaffThunderbolt.h"
#include "Engine/OverlapResult.h"
#include "Engine/DamageEvents.h"
#include "Stat/CharacterDataStat.h"

AStaffThunderbolt::AStaffThunderbolt()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	UpPlane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UpPlane"));
	UpPlane->SetupAttachment(Root);
	UpPlane->SetCollisionProfileName(TEXT("NoCollision"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> UpPlaneRef(TEXT("/Script/Engine.StaticMesh'/Game/ParagonGideon/FX/Meshes/Heroes/Gideon/SM_Ult_Runes_Inner.SM_Ult_Runes_Inner'"));
	if (UpPlaneRef.Object)
	{
		UpPlane->SetStaticMesh(UpPlaneRef.Object);
	}

	DownPlane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DownPlane"));
	DownPlane->SetupAttachment(Root);
	DownPlane->SetCollisionProfileName(TEXT("NoCollision"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> DownPlaneRef(TEXT("/Script/Engine.StaticMesh'/Game/ParagonGideon/FX/Meshes/Heroes/Gideon/SM_Ult_Runes_Outer.SM_Ult_Runes_Outer'"));
	if (DownPlaneRef.Object)
	{
		DownPlane->SetStaticMesh(DownPlaneRef.Object);
	}

	LifeTime = 5.f;
	Damage = Stat->Staff_R_Damage;
}

void AStaffThunderbolt::BeginPlay()
{
	Super::BeginPlay();
	
}

void AStaffThunderbolt::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LifeTime -= DeltaTime;
	if (LifeTime <= 0.f)
	{
		Destroy();
	}

}

void AStaffThunderbolt::ActiveThunderbolt()
{
	if (CheckInArea())
	{
		FDamageEvent DamageEvent;
		for (const auto& OverlapResult : OverlapResults)
		{
			OverlapResult.GetActor()->TakeDamage(Damage, DamageEvent, OverlapResult.GetActor()->GetInstigatorController(), GetOwner());
		}
		DrawDebugSphere(GetWorld(), GetActorLocation(), 350.f, 32, FColor::Green, false, 3.f);
	}
}

bool AStaffThunderbolt::CheckInArea()
{
	const float Radius = 350.f;

	FVector Origin = GetActorLocation();
	FCollisionQueryParams Params(NAME_None, true, GetOwner()); //GetOwner 꼭 설정해주기

	return GetWorld()->OverlapMultiByChannel(OverlapResults, Origin, FQuat::Identity, ECC_GameTraceChannel2, FCollisionShape::MakeSphere(Radius), Params);
}

