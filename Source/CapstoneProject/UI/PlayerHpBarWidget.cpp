// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerHpBarWidget.h"
#include "Interface/PlayerHpBarWidgetInterface.h"
#include "Components/ProgressBar.h"

UPlayerHpBarWidget::UPlayerHpBarWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MaxHp = -1.0f;
}

void UPlayerHpBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HpProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PlayerHpBar")));
	ensure(HpProgressBar);

	IPlayerHpBarWidgetInterface* Interface = Cast<IPlayerHpBarWidgetInterface>(GetOwner());
	if (Interface)
	{
		Interface->SetupPlayerHpBarWidget(this);
	}
}

void UPlayerHpBarWidget::UpdateHpBar(float NewCurrentHp)
{
	HpProgressBar->SetPercent(NewCurrentHp / MaxHp);
}

void UPlayerHpBarWidget::SetMaxHp(float NewMaxHp)
{
	MaxHp = NewMaxHp;
}