// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Skill_R_Base.h"

USkill_R_Base::USkill_R_Base()
{
	CurrentShortcutKey = EShortcutkey::R;
}

void USkill_R_Base::ExecuteSkill()
{
	Super::ExecuteSkill();
}
