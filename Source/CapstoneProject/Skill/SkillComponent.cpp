// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillComponent.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

USkillComponent::USkillComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void USkillComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void USkillComponent::BeginStingMontage()
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();

	Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	AnimInstance->Montage_Play(SwordStingMontage);

	FOnMontageEnded MontageEnd;
	MontageEnd.BindUObject(this, &USkillComponent::EndStingMontage);
	AnimInstance->Montage_SetEndDelegate(MontageEnd, SwordStingMontage);
}

void USkillComponent::EndStingMontage(UAnimMontage* Target, bool IsProperlyEnded)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}



