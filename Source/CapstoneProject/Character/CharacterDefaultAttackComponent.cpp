// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterDefaultAttackComponent.h"
#include "Character/CharacterComboAttackData.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UCharacterDefaultAttackComponent::UCharacterDefaultAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UCharacterDefaultAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	Character = CastChecked<ACharacter>(GetOwner());
}


void UCharacterDefaultAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UCharacterDefaultAttackComponent::BeginAttack()
{
	if (CurrentCombo == 0)
	{
		BeginDefaultAttack();
		return;
	}

	if (!ComboTimer.IsValid())
	{
		HasNextComboCommand = false;
	}
	else
	{
		HasNextComboCommand = true;
	}
}

void UCharacterDefaultAttackComponent::BeginDefaultAttack()
{
	CurrentCombo = 1;

	Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

	UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(DefaultAttackMontage);

	FOnMontageEnded MontageEnded;
	MontageEnded.BindUObject(this, &UCharacterDefaultAttackComponent::EndDefaultAttack);
	AnimInstance->Montage_SetEndDelegate(MontageEnded, DefaultAttackMontage);

	ComboTimer.Invalidate();
	SetComboTimer();
}

void UCharacterDefaultAttackComponent::EndDefaultAttack(UAnimMontage* Target, bool IsProperlyEnded)
{
	ensure(CurrentCombo != 0);
	CurrentCombo = 0;
	Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void UCharacterDefaultAttackComponent::SetComboTimer()
{
	int32 ComboIndex = CurrentCombo - 1;
	ensure(ComboData->EffectiveFrameCount.IsValidIndex(ComboIndex));

	float ComboEffectiveTime = (ComboData->EffectiveFrameCount[ComboIndex] / ComboData->FrameRate);
	if (ComboEffectiveTime > 0.0f)
	{
		GetWorld()->GetTimerManager().SetTimer(ComboTimer, this, &UCharacterDefaultAttackComponent::CheckCombo, ComboEffectiveTime, false);
	}
}

void UCharacterDefaultAttackComponent::CheckCombo()
{
	ComboTimer.Invalidate();
	if (HasNextComboCommand)
	{
		UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();

		CurrentCombo = FMath::Clamp(CurrentCombo + 1, 1, ComboData->MaxComboCount);
		FName NextSection = *FString::Printf(TEXT("%s%d"), *ComboData->MontageSectionNamePrefix, CurrentCombo);
		AnimInstance->Montage_JumpToSection(NextSection, DefaultAttackMontage);
		SetComboTimer();
		HasNextComboCommand = false;
	}
}

