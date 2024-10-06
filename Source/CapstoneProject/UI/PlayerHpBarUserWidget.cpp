// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerHpBarUserWidget.h"

void UPlayerHpBarUserWidget::SetOwningActor(AActor* Actor)
{
	OwningActor = Actor;
}

AActor* UPlayerHpBarUserWidget::GetOwner() const
{
	return OwningActor;
}

