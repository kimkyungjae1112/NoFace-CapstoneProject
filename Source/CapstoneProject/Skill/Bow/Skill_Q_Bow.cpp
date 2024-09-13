// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Bow/Skill_Q_Bow.h"

ASkill_Q_Bow::ASkill_Q_Bow()
{
}

void ASkill_Q_Bow::ExecuteSkill()
{
	Super::ExecuteSkill();

	UE_LOG(LogTemp, Display, TEXT("Bow Skill Q"));
}
