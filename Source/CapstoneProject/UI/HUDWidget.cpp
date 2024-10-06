// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUDWidget.h"
#include "Interface/PlayerHUDInterface.h"
#include "PlayerHpBarWidget.h"
#include "PlayerExpBarWidget.h"

UHUDWidget::UHUDWidget(const FObjectInitializer& OnjectInitializer) : Super(OnjectInitializer)
{

}

void UHUDWidget::SetMaxHp(float NewMaxHp)
{
	HpBar->SetMaxHp(NewMaxHp);
}

void UHUDWidget::UpdateHpBar(float NewCurrentHp)
{
	HpBar->UpdateHpBar(NewCurrentHp);
}

void UHUDWidget::UpdateExpBar(float NewCurrentExp)
{
	ExpBar->UpdateExpBar(NewCurrentExp);
}


void UHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HpBar = Cast<UPlayerHpBarWidget>(GetWidgetFromName(TEXT("WidgetHpBar")));
	ensure(HpBar);

	ExpBar = Cast<UPlayerExpBarWidget>(GetWidgetFromName(TEXT("WidgetExpBar")));
	ensure(ExpBar);

	IPlayerHUDInterface* HUDPawn = Cast< IPlayerHUDInterface>(GetOwningPlayerPawn());
	if (HUDPawn)
	{
		HUDPawn->SetupHUDWidget(this);
	}

}
