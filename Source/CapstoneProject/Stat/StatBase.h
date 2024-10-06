// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatBase.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHpZero);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHpChanged, float /* CurrentHp */);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnExpChanged, float /* CurrentExp */);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CAPSTONEPROJECT_API UStatBase : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStatBase();

public:
	FOnHpZero OnHpZero;
	FOnHpChanged OnHpChanged;
	FOnExpChanged OnExpChanged;
		
};
