// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Sword/Skill_Q_Sword.h"

USkill_Q_Sword::USkill_Q_Sword()
{
}

void USkill_Q_Sword::ExecuteSkill()
{
	Super::ExecuteSkill();

	UE_LOG(LogTemp, Display, TEXT("Sword Skill Q"));
}
