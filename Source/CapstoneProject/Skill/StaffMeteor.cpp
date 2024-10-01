// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/StaffMeteor.h"
#include "Components/BoxComponent.h"
#include "Stat/CharacterDataStat.h"

AStaffMeteor::AStaffMeteor()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetupAttachment(Root);
	Box->OnComponentHit.AddDynamic(this, &AStaffMeteor::OnHit);

	Meteor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Meteor"));
	Meteor->SetupAttachment(Root);
	Meteor->SetCollisionProfileName(TEXT("NoCollision"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeteorRef(TEXT("/Script/Engine.StaticMesh'/Game/ParagonGideon/FX/Meshes/Heroes/Gideon/SM_Meteor.SM_Meteor'"));
	if (MeteorRef.Object)
	{
		Meteor->SetStaticMesh(MeteorRef.Object);
	}

	MeteorSpline = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeteorSpline"));
	MeteorSpline->SetupAttachment(Meteor);
	MeteorSpline->SetCollisionProfileName(TEXT("NoCollision"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeteorSplineRef(TEXT("/Script/Engine.StaticMesh'/Game/ParagonGideon/FX/Meshes/Heroes/Gideon/SM_Meteor_Spline.SM_Meteor_Spline'"));
	if (MeteorSplineRef.Object)
	{
		MeteorSpline->SetStaticMesh(MeteorSplineRef.Object);
	}

	MoveSpeed = 1500.f;
	Damage = Stat->Staff_Q_Damage;
	Destination = FVector::ZeroVector;
	bStart = false;
}

void AStaffMeteor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AStaffMeteor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bStart)
	{
		FVector Origin = GetActorLocation();
		SetActorLocation(FMath::VInterpConstantTo(Origin, Destination, DeltaTime, MoveSpeed));
	}
}

void AStaffMeteor::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Display, TEXT("충돌"));
	Destroy();

}

void AStaffMeteor::Init(const FVector& InDestination)
{
	Destination = InDestination;
	bStart = true;
}

