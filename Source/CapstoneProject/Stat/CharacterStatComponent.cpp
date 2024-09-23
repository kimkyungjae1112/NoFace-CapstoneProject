// Fill out your copyright notice in the Description page of Project Settings.


#include "Stat/CharacterStatComponent.h"
#include "Stat/CharacterDataStat.h"

UCharacterStatComponent::UCharacterStatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UCharacterDataStat> DataStatRef(TEXT("/Script/CapstoneProject.CharacterDataStat'/Game/No-Face/Character/Stat/DA_CharacterStatData.DA_CharacterStatData'"));
	if (DataStatRef.Object)
	{
		DataStat = DataStatRef.Object;
	}

	/* 이렇게 해야 하나의 에셋으로 캐릭터의 스텟을 관리하기 편한거 같음 */
	CurrentHp = DataStat->Hp;
	CurrentMp = DataStat->Mp;
	CurrentDamage = DataStat->Damage;
	CurrentRange = DataStat->Range;
}


void UCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	
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

