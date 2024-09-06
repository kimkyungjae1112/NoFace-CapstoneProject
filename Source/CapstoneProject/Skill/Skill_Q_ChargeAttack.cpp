// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Skill_Q_ChargeAttack.h"

USkill_Q_ChargeAttack::USkill_Q_ChargeAttack()
{
}

void USkill_Q_ChargeAttack::ExecuteSkill()
{
	Super::ExecuteSkill();

	UE_LOG(LogTemp, Display, TEXT("Q Class ChargeAttack Skill Execute"));
}
