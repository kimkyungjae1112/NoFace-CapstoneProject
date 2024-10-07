// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerExpBarWidgetComponent.h"
#include "PlayerHpBarUserWidget.h"

void UPlayerExpBarWidgetComponent::InitWidget()
{
	Super::InitWidget();
	UPlayerHpBarUserWidget* PlayerExpBarUserWidget = Cast<UPlayerHpBarUserWidget>(GetWidget());
	if (PlayerExpBarUserWidget)
	{
		PlayerExpBarUserWidget->SetOwningActor(GetOwner());
	}
}