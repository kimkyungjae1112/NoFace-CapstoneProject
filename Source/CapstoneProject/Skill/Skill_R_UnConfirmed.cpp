// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Skill_R_UnConfirmed.h"

USkill_R_UnConfirmed::USkill_R_UnConfirmed()
{
}

void USkill_R_UnConfirmed::ExecuteSkill()
{
	Super::ExecuteSkill();

	UE_LOG(LogTemp, Display, TEXT("R Class UnConfimred Skill Execute"));
}
