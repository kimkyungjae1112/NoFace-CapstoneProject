// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Sword/Skill_E_Sword.h"

ASkill_E_Sword::ASkill_E_Sword()
{
}

void ASkill_E_Sword::ExecuteSkill()
{
	Super::ExecuteSkill();

	UE_LOG(LogTemp, Display, TEXT("Sword Skill E"));
}
