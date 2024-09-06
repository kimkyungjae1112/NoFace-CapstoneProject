// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Skill_E_UnConfirmed.h"

USkill_E_UnConfirmed::USkill_E_UnConfirmed()
{
}

void USkill_E_UnConfirmed::ExecuteSkill()
{
	Super::ExecuteSkill();

	UE_LOG(LogTemp, Display, TEXT("E Class UnConfimred Skill Execute"));
}
