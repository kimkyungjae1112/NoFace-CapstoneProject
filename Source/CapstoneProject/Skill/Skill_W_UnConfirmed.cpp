// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Skill_W_UnConfirmed.h"

USkill_W_UnConfirmed::USkill_W_UnConfirmed()
{
}

void USkill_W_UnConfirmed::ExecuteSkill()
{
	Super::ExecuteSkill();

	UE_LOG(LogTemp, Display, TEXT("W Class UnConfimred Skill Execute"));
}
