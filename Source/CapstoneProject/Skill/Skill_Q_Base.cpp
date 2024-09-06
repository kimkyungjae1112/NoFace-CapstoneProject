// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Skill_Q_Base.h"

USkill_Q_Base::USkill_Q_Base()
{
	CurrentShortcutKey = EShortcutkey::Q;
}

void USkill_Q_Base::ExecuteSkill()
{
	Super::ExecuteSkill();

	UE_LOG(LogTemp, Display, TEXT("Q_Base Class Skill Execute"));
}
