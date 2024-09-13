// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Staff/Skill_W_Staff.h"

ASkill_W_Staff::ASkill_W_Staff()
{
}

void ASkill_W_Staff::ExecuteSkill()
{
	Super::ExecuteSkill();

	UE_LOG(LogTemp, Display, TEXT("Staff Skill W"));
}
