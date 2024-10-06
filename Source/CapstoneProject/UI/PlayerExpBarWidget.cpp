// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerExpBarWidget.h"
#include "Interface/PlayerHpBarWidgetInterface.h"
#include "Interface/PlayerExpBarWidgetInterface.h"
#include "Components/ProgressBar.h"

UPlayerExpBarWidget::UPlayerExpBarWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UPlayerExpBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ExpProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PlayerExpBar")));
	ensure(ExpProgressBar);

	IPlayerExpBarWidgetInterface* Interface = Cast<IPlayerExpBarWidgetInterface>(GetOwner());
	if (Interface)
	{
		Interface->SetupPlayerExpBarWidget(this);
	}
}

void UPlayerExpBarWidget::UpdateExpBar(float NewCurrentHp)
{
	ExpProgressBar->SetPercent(NewCurrentHp / 100.0f);
}