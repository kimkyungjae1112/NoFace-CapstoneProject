// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Arrow.h"
#include "Components/BoxComponent.h"
#include "Engine/DamageEvents.h"
#include "Stat/CharacterDataStat.h"

AArrow::AArrow()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetupAttachment(Root);
	Box->SetCollisionProfileName(TEXT("Arrow"));
	Box->OnComponentHit.AddDynamic(this, &AArrow::OnHit);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshRef(TEXT("/Script/Engine.StaticMesh'/Game/No-Face/Weapon/Bow/Mesh/SM_Arrow_A.SM_Arrow_A'"));
	if (MeshRef.Object)
	{
		Mesh->SetStaticMesh(MeshRef.Object);
	}

	Direction = FVector::ZeroVector;
	Damage = Stat->BowDamage;
	MoveSpeed = Stat->BowSpeed;
	LifeTime = Stat->BowLifeTime;
}

void AArrow::BeginPlay()
{
	Super::BeginPlay();
	
}

void AArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation() + (Direction * MoveSpeed * DeltaTime);
	SetActorLocation(NewLocation);

	LifeTime -= DeltaTime;
	if (LifeTime <= 0.f)
	{
		Destroy();
	}
}

void AArrow::Init(const FVector& InDirection, const FVector& CurrentLocation, const FRotator& CurrentRotation)
{
	SetActorLocation(CurrentLocation);
	SetActorRotation(CurrentRotation);
	Direction = InDirection;
}

void AArrow::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != this)
	{
		FDamageEvent DamageEvent;
		OtherActor->TakeDamage(Damage, DamageEvent, GetWorld()->GetFirstPlayerController(), this);
		UE_LOG(LogTemp, Display, TEXT("화살 히트"));
		Destroy();
	}
}



