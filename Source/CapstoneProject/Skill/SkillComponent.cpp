// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillComponent.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/CharacterSkillMontageData.h"

USkillComponent::USkillComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void USkillComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void USkillComponent::PlaySkill(int32 Index)
{
	BeginStingMontage(Index);
}

void USkillComponent::BeginStingMontage(int32 Index)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();

	Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	AnimInstance->Montage_Play(SkillMontageData->SwordMontages[Index]);

	FOnMontageEnded MontageEnd;
	MontageEnd.BindUObject(this, &USkillComponent::EndStingMontage);
	AnimInstance->Montage_SetEndDelegate(MontageEnd, SkillMontageData->SwordMontages[Index]);
}

void USkillComponent::EndStingMontage(UAnimMontage* Target, bool IsProperlyEnded)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}



