// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Bow/Skill_E_Bow.h"

ASkill_E_Bow::ASkill_E_Bow()
{
}

void ASkill_E_Bow::ExecuteSkill()
{
	Super::ExecuteSkill();

	UE_LOG(LogTemp, Display, TEXT("Bow Skill E"));
}
