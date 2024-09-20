// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Arrow.h"
#include "Components/BoxComponent.h"
#include "Engine/DamageEvents.h"

AArrow::AArrow()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetupAttachment(Root);
	Box->SetCollisionProfileName(TEXT("Arrow"));
	Box->OnComponentHit.AddDynamic(this, &AArrow::OnHit);
	Box->OnComponentBeginOverlap.AddDynamic(this, &AArrow::OnBeginOverlap);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshRef(TEXT("/Script/Engine.StaticMesh'/Game/MRPGT/StaticMeshes/Weapons/SM_Arrow_A.SM_Arrow_A'"));
	if (MeshRef.Object)
	{
		Mesh->SetStaticMesh(MeshRef.Object);
	}

	Direction = FVector::ZeroVector;
	Damage = 50.f;
	MoveSpeed = 500.f;
	LifeTime = 5.f;
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

	DrawDebugBox(GetWorld(), GetActorLocation(), Box->GetScaledBoxExtent(), FColor::Red, false);
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

void AArrow::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		FDamageEvent DamageEvent;
		OtherActor->TakeDamage(Damage, DamageEvent, GetWorld()->GetFirstPlayerController(), this);
		UE_LOG(LogTemp, Display, TEXT("화살 오버랩"));
		Destroy();
	}
}

