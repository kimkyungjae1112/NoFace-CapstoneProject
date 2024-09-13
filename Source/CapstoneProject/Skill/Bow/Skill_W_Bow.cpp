// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Bow/Skill_W_Bow.h"

ASkill_W_Bow::ASkill_W_Bow()
{
}

void ASkill_W_Bow::ExecuteSkill()
{
	Super::ExecuteSkill();

	UE_LOG(LogTemp, Display, TEXT("Bow Skill W"));
}
