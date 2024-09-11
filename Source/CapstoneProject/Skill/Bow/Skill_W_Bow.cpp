// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Bow/Skill_W_Bow.h"

USkill_W_Bow::USkill_W_Bow()
{
}

void USkill_W_Bow::ExecuteSkill()
{
	Super::ExecuteSkill();

	UE_LOG(LogTemp, Display, TEXT("Bow Skill W"));
}
