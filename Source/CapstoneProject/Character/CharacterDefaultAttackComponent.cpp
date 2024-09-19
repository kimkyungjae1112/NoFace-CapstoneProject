// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterDefaultAttackComponent.h"
#include "Character/CharacterComboAttackData.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UCharacterDefaultAttackComponent::UCharacterDefaultAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	CurrentWeaponType = 0;
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

void UCharacterDefaultAttackComponent::SetWeaponType(const int32& InCurrentWeaponType)
{
	CurrentWeaponType = InCurrentWeaponType;
}

void UCharacterDefaultAttackComponent::BeginAttack()
{
	if (CurrentCombo == 0)
	{
		switch (CurrentWeaponType)
		{
		case 0:
			BeginSwordDefaultAttack();
			return;
		case 1:
			BeginBowDefaultAttack();
			return;
		case 2:
			BeginStaffDefaultAttack();
			return;
		default:
			return;
		}
	}

	if (!SwordComboTimer.IsValid())
	{
		HasNextComboCommand = false;
	}
	else
	{
		HasNextComboCommand = true;
	}
}

void UCharacterDefaultAttackComponent::BeginSwordDefaultAttack()
{
	CurrentCombo = 1;

	Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

	UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(SwordDefaultAttackMontage);

	FOnMontageEnded MontageEnded;
	MontageEnded.BindUObject(this, &UCharacterDefaultAttackComponent::EndSwordDefaultAttack);
	AnimInstance->Montage_SetEndDelegate(MontageEnded, SwordDefaultAttackMontage);

	SwordComboTimer.Invalidate();
	SetSwordComboTimer();
}

void UCharacterDefaultAttackComponent::EndSwordDefaultAttack(UAnimMontage* Target, bool IsProperlyEnded)
{
	ensure(CurrentCombo != 0);
	CurrentCombo = 0;
	Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void UCharacterDefaultAttackComponent::SetSwordComboTimer()
{
	int32 ComboIndex = CurrentCombo - 1;
	ensure(SwordComboData->EffectiveFrameCount.IsValidIndex(ComboIndex));

	float ComboEffectiveTime = (SwordComboData->EffectiveFrameCount[ComboIndex] / SwordComboData->FrameRate);
	if (ComboEffectiveTime > 0.0f)
	{
		GetWorld()->GetTimerManager().SetTimer(SwordComboTimer, this, &UCharacterDefaultAttackComponent::CheckSwordCombo, ComboEffectiveTime, false);
	}
}

void UCharacterDefaultAttackComponent::CheckSwordCombo()
{
	SwordComboTimer.Invalidate();
	if (HasNextComboCommand)
	{
		UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();

		CurrentCombo = FMath::Clamp(CurrentCombo + 1, 1, SwordComboData->MaxComboCount);
		FName NextSection = *FString::Printf(TEXT("%s%d"), *SwordComboData->MontageSectionNamePrefix, CurrentCombo);
		AnimInstance->Montage_JumpToSection(NextSection, SwordDefaultAttackMontage);
		SetSwordComboTimer();
		HasNextComboCommand = false;
	}
}

void UCharacterDefaultAttackComponent::BeginBowDefaultAttack()
{
	UE_LOG(LogTemp, Display, TEXT("활 기본 공격"));

}

void UCharacterDefaultAttackComponent::EndBowDefaultAttack(UAnimMontage* Target, bool IsProperlyEnded)
{
}

void UCharacterDefaultAttackComponent::SetBowComboTimer()
{
}

void UCharacterDefaultAttackComponent::CheckBowCombo()
{
}

void UCharacterDefaultAttackComponent::BeginStaffDefaultAttack()
{
	UE_LOG(LogTemp, Display, TEXT("지팡이 기본 공격"));
}

void UCharacterDefaultAttackComponent::EndStaffDefaultAttack(UAnimMontage* Target, bool IsProperlyEnded)
{
}

void UCharacterDefaultAttackComponent::SetStaffComboTimer()
{
}

void UCharacterDefaultAttackComponent::CheckStaffCombo()
{
}

