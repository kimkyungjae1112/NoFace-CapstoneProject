// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnemyPtrWidget.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROJECT_API UEnemyPtrWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UEnemyPtrWidget(const FObjectInitializer& ObjectInitializer);

	FORCEINLINE void SetOwningActor(AActor* Owner) { OwningActor = Owner; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Owner")
	TObjectPtr<AActor> OwningActor;
};
