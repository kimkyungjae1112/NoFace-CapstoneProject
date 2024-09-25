// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/StaffUpGround.h"
#include "Engine/OverlapResult.h"
#include "Enemy/EnemyBase.h"

AStaffUpGround::AStaffUpGround()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshRef(TEXT("/Script/Engine.StaticMesh'/Game/No-Face/Effect/Staff/Mesh/SM_Meteor_Cine.SM_Meteor_Cine'"));
	if (MeshRef.Object)
	{
		Mesh->SetStaticMesh(MeshRef.Object);
	}

}

void AStaffUpGround::BeginPlay()
{
	Super::BeginPlay();
	
}

void AStaffUpGround::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStaffUpGround::ActiveGroundUp()
{
	if (CheckInArea())
	{
		for (const auto& OverlapResult : OverlapResults)
		{
			AEnemyBase* Enemy = Cast<AEnemyBase>(OverlapResult.GetActor());
			float Distance = FVector::Dist(Enemy->GetActorLocation(), GetActorLocation());

			Enemy->LaunchCharacter(FVector(0.f, 0.f, 1500.f * (1 / Distance)), false, true);
			//Enemy->OnLaunched(FVector(0.f, 0.f, 1500.f * (1 / Distance)), false, true);
			UE_LOG(LogTemp, Display, TEXT("Enemy Name : %s"), *Enemy->GetActorNameOrLabel());
			UE_LOG(LogTemp, Display, TEXT("Enemy Location : %f"), Enemy->GetActorLocation().Z);
		}
	}
}

bool AStaffUpGround::CheckInArea()
{
	const float Radius = 150.f;

	FVector Origin = GetActorLocation();
	FCollisionQueryParams Params(NAME_None, true, GetOwner()); //GetOwner 꼭 설정해주기
	DrawDebugSphere(GetWorld(), Origin, Radius, 32, FColor::Red, false);

	return GetWorld()->OverlapMultiByChannel(OverlapResults, Origin, FQuat::Identity, ECC_GameTraceChannel2, FCollisionShape::MakeSphere(Radius), Params);
}

