// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerHpBarWidgetComponent.h"
#include "PlayerHpBarUserWidget.h"

void UPlayerHpBarWidgetComponent::InitWidget()
{
	Super::InitWidget();
	UPlayerHpBarUserWidget* PlayerHpBarUserWidget = Cast<UPlayerHpBarUserWidget>(GetWidget());
	if (PlayerHpBarUserWidget)
	{
		PlayerHpBarUserWidget->SetOwningActor(GetOwner());
	}
}