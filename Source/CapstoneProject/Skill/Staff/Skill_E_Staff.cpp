// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Staff/Skill_E_Staff.h"

ASkill_E_Staff::ASkill_E_Staff()
{
}

void ASkill_E_Staff::ExecuteSkill()
{
	Super::ExecuteSkill();

	UE_LOG(LogTemp, Display, TEXT("Staff Skill E"));
}
