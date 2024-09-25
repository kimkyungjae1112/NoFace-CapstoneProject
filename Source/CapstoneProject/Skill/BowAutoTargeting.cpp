// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/BowAutoTargeting.h"
#include "Components/BoxComponent.h"
#include "Enemy/EnemyBase.h"

ABowAutoTargeting::ABowAutoTargeting()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetupAttachment(Root);
	Box->OnComponentBeginOverlap.AddDynamic(this, &ABowAutoTargeting::OnBoxBeginOverlap);
}

void ABowAutoTargeting::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABowAutoTargeting::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentExtent = Box->GetScaledBoxExtent();
	CurrentExtent.X += 5.f;

	if (CurrentExtent.X <= 400.f)
	{
		Box->SetBoxExtent(CurrentExtent);
	}
	else
	{
		Destroy();
	}
}

void ABowAutoTargeting::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AEnemyBase* Enemy = Cast<AEnemyBase>(OtherActor))
	{
		Enemys.Add(Enemy);
		DrawDebugSphere(GetWorld(), Enemy->GetActorLocation(), 10.f, 12, FColor::Green, false, 5.f);
	}
}


