// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Bow/Skill_R_Bow.h"

USkill_R_Bow::USkill_R_Bow()
{
}

void USkill_R_Bow::ExecuteSkill()
{
	Super::ExecuteSkill();

	UE_LOG(LogTemp, Display, TEXT("Bow Skill R"));
}
