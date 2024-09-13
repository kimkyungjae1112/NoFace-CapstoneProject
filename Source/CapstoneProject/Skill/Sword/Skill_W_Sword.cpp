// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Sword/Skill_W_Sword.h"

ASkill_W_Sword::ASkill_W_Sword()
{
}

void ASkill_W_Sword::ExecuteSkill()
{
	Super::ExecuteSkill();

	UE_LOG(LogTemp, Display, TEXT("Sword Skill W"));
}
