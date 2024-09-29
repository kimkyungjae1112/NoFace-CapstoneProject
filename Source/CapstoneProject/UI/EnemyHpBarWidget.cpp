// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/EnemyHpBarWidget.h"
#include "Components/ProgressBar.h"
#include "Interface/EnemyHpBarWidgetInterface.h"

UEnemyHpBarWidget::UEnemyHpBarWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MaxHp = -1.f;
}

void UEnemyHpBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HpBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("Pb_HpBar")));
	ensure(HpBar);

	IEnemyHpBarWidgetInterface* Interface = Cast<IEnemyHpBarWidgetInterface>(OwningActor);
	if (Interface)
	{
		Interface->SetupHpBarWidget(this);
	}
}

void UEnemyHpBarWidget::UpdateHpBar(float NewHp)
{
	HpBar->SetPercent(NewHp / MaxHp);
}

void UEnemyHpBarWidget::SetMaxHp(float InMaxHp)
{
	MaxHp = InMaxHp;
}
