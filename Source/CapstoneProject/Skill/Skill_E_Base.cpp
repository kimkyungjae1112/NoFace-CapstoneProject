// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Skill_E_Base.h"

USkill_E_Base::USkill_E_Base()
{
	CurrentShortcutKey = EShortcutkey::E;
}

void USkill_E_Base::ExecuteSkill()
{
	Super::ExecuteSkill();
}
