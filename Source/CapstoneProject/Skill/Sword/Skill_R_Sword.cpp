// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Sword/Skill_R_Sword.h"

USkill_R_Sword::USkill_R_Sword()
{
}

void USkill_R_Sword::ExecuteSkill()
{
	Super::ExecuteSkill();

	UE_LOG(LogTemp, Display, TEXT("Sword Skill R"));
}
