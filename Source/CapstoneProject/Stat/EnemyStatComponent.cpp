// Fill out your copyright notice in the Description page of Project Settings.


#include "Stat/EnemyStatComponent.h"
#include "Stat/EnemyDataStat.h"

UEnemyStatComponent::UEnemyStatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UEnemyDataStat> EnemyDataStatRef(TEXT("/Script/CapstoneProject.EnemyDataStat'/Game/No-Face/Enemy/Stat/DA_EnemyStatData.DA_EnemyStatData'"));
	if (EnemyDataStatRef.Object)
	{
		DataStat = EnemyDataStatRef.Object;
	}
	
	CurrentHp = DataStat->Hp;
	CurrentMp = DataStat->Mp;
	CurrentDamage = DataStat->Damage;
	CurrentRange = DataStat->Range;
	CurrentMoveSpeed = DataStat->MoveSpeed;
}


void UEnemyStatComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UEnemyStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

float UEnemyStatComponent::ApplyDamage(float InDamage)
{
	float ActualDamage = FMath::Clamp(InDamage, 0, InDamage);
	float PrevHp = CurrentHp;

	SetHp(PrevHp - ActualDamage);
	if (CurrentHp < KINDA_SMALL_NUMBER)
	{
		OnHpZero.Broadcast();
	}

	return 0.0f;
}

void UEnemyStatComponent::SetHp(float ChangeHp)
{
	CurrentHp = ChangeHp;
	UE_LOG(LogTemp, Display, TEXT("Current Hp : %f"), CurrentHp);
	OnHpChanged.Broadcast(CurrentHp);
}

