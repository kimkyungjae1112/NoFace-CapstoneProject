// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Bow/Skill_R_Bow.h"

ASkill_R_Bow::ASkill_R_Bow()
{
}

void ASkill_R_Bow::ExecuteSkill()
{
	Super::ExecuteSkill();

	UE_LOG(LogTemp, Display, TEXT("Bow Skill R"));
}
