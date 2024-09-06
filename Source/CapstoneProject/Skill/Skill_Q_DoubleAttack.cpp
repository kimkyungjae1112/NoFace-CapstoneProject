// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Skill_Q_DoubleAttack.h"

USkill_Q_DoubleAttack::USkill_Q_DoubleAttack()
{
}

void USkill_Q_DoubleAttack::ExecuteSkill()
{
	Super::ExecuteSkill();

	UE_LOG(LogTemp, Display, TEXT("Q Class DoubleAttack Skill Execute"));
}
