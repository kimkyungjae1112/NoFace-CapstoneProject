// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SwordAura.h"
#include "Components/BoxComponent.h"
#include "Engine/DamageEvents.h"
#include "Stat/CharacterDataStat.h"

ASwordAura::ASwordAura()
{
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;
	Box->OnComponentBeginOverlap.AddDynamic(this, &ASwordAura::OnBeginOverlap);

	MoveDirection = FVector::ZeroVector;
	Damage = Stat->Sword_R_Damage;
	MoveSpeed = Stat->Sword_R_MoveSpeed;
	LifeTime = Stat->Sword_R_LifeTime;

	Color = FColor::Red;
}

void ASwordAura::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASwordAura::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector NewLocation = GetActorLocation() + (MoveDirection * MoveSpeed * DeltaTime);
	SetActorLocation(NewLocation);

	LifeTime -= DeltaTime;
	if (LifeTime <= 0.f)
	{
		Destroy();	//LifeTime 동안 검기가 움직이도록 설정
	}

	DrawDebugBox(GetWorld(), GetActorLocation(), Box->GetScaledBoxExtent(), Color, false);
}

void ASwordAura::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		FDamageEvent DamageEvent;
		OtherActor->TakeDamage(Damage, DamageEvent, GetWorld()->GetFirstPlayerController(), this);
		Color = FColor::Green;
	}
}

void ASwordAura::Init(const FVector& InMoveDirection)
{
	MoveDirection = InMoveDirection;
}



