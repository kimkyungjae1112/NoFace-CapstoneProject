// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Staff/Skill_Q_Staff.h"

ASkill_Q_Staff::ASkill_Q_Staff()
{
}

void ASkill_Q_Staff::ExecuteSkill()
{
	Super::ExecuteSkill();

	UE_LOG(LogTemp, Display, TEXT("Staff Skill Q"));
}
