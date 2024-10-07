// Fill out your copyright notice in the Description page of Project Settings.


#include "Stat/CharacterStatComponent.h"
#include "Stat/CharacterDataStat.h"
#include "Enemy/EnemyBase.h"


UCharacterStatComponent::UCharacterStatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UCharacterDataStat> DataStatRef(TEXT("/Script/CapstoneProject.CharacterDataStat'/Game/No-Face/Character/Stat/DA_CharacterStatData.DA_CharacterStatData'"));
	if (DataStatRef.Object)
	{
		DataStat = DataStatRef.Object;
	}

	/* 이렇게 해야 하나의 에셋으로 캐릭터의 스텟을 관리하기 편한거 같음 */
	MaxHp = DataStat->MaxHp;
	CurrentHp = DataStat->Hp;
	CurrentExp = DataStat->Exp;
	CurrentLevel = 1;
	
	bWantsInitializeComponent = true;

}


void UCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	AEnemyBase::OnDead.BindUObject(this, &UCharacterStatComponent::SetExp);
}

void UCharacterStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

float UCharacterStatComponent::ApplyDamage(float InDamage)
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

void UCharacterStatComponent::SetHp(float ChangeHp)
{
	CurrentHp = ChangeHp;
	UE_LOG(LogTemp, Display, TEXT("Current Hp : %f"), CurrentHp);
	OnHpChanged.Broadcast(CurrentHp);
}

void UCharacterStatComponent::SetExp(float InExp)
{
	UE_LOG(LogTemp, Display, TEXT("Get Exp Amount : %f"), InExp);
	CurrentExp = CurrentExp + InExp;
	UE_LOG(LogTemp, Display, TEXT("Current Exp : %f,  //  Current Level : %d"), CurrentExp, CurrentLevel);
	OnExpChanged.Broadcast(CurrentExp);
}

