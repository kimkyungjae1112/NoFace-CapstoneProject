// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Staff/Skill_R_Staff.h"

ASkill_R_Staff::ASkill_R_Staff()
{
}

void ASkill_R_Staff::ExecuteSkill()
{
	Super::ExecuteSkill();

	UE_LOG(LogTemp, Display, TEXT("Staff Skill R"));
}
