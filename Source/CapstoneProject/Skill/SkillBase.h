// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SkillBase.generated.h"

UENUM(BlueprintType)
enum class EShortcutkey : uint8
{
	Q = 0,
	W,
	E,
	R
};

/**
 * 
 */
UCLASS(Abstract)
class CAPSTONEPROJECT_API USkillBase : public UObject
{
	GENERATED_BODY()

public:
	/* SkillBase를 상속받은 클래스는 반드시 이 가상함수를 재정의 하도록 합시다. */
	virtual void ExecuteSkill(); /*PURE_VIRTUAL(USkillBase::ExecuteSkill, );*/
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShortcutKey")
	EShortcutkey CurrentShortcutKey;
};
