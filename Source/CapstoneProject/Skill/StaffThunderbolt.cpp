// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/StaffThunderbolt.h"

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
}

void AStaffThunderbolt::BeginPlay()
{
	Super::BeginPlay();
	
}

void AStaffThunderbolt::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

