// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkillHitCheckComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CAPSTONEPROJECT_API USkillHitCheckComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USkillHitCheckComponent();

protected:
	virtual void BeginPlay() override;


		
};
