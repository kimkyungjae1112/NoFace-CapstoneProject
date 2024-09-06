// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Skill_W_Base.h"

USkill_W_Base::USkill_W_Base()
{
	CurrentShortcutKey = EShortcutkey::W;
}

void USkill_W_Base::ExecuteSkill()
{
	Super::ExecuteSkill();

	UE_LOG(LogTemp, Display, TEXT("W_Base Class Skill Execute"));
}
