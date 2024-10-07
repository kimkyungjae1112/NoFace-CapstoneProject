// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHpBarUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROJECT_API UPlayerHpBarUserWidget : public UUserWidget
{
	GENERATED_BODY()
	

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Actor")
	TObjectPtr<AActor> OwningActor;

public:
	void SetOwningActor(class AActor* Actor);
	class AActor* GetOwner() const;
};
