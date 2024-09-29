// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/EnemyHpBarWidgetComponent.h"
#include "UI/EnemyPtrWidget.h"

void UEnemyHpBarWidgetComponent::InitWidget()
{
	Super::InitWidget();

	UEnemyPtrWidget* UserWidget = Cast<UEnemyPtrWidget>(GetWidget());
	if (UserWidget)
	{
		UserWidget->SetOwningActor(GetOwner());
	}
}
