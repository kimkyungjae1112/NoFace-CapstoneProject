// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "CharacterWarrior.generated.h"

UCLASS()
class CAPSTONEPROJECT_API ACharacterWarrior : public ACharacterBase
{
	GENERATED_BODY()

public:
	ACharacterWarrior();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void Q_Skill() override;
	virtual void W_Skill() override;
	virtual void E_Skill() override;
	virtual void R_Skill() override;
};
