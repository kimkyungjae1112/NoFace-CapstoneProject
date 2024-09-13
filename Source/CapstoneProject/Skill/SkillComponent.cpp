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

	Character = Cast<ACharacter>(GetOwner());
}

void USkillComponent::PlaySkill_Q()
{
	switch (CurrentWeaponType)
	{
	case 0:
		BeginSwordSting();
		break;
	case 1:
		BeginBowSeveralArrows();
		break;
	case 2:
		BeginStaffFireball();
		break;
	default:
		break;
	}
}

void USkillComponent::PlaySkill_W()
{
	switch (CurrentWeaponType)
	{
	case 0:
		BeginSwordWhirlwind();
		break;
	case 1:
		BeginBowExplosionArrow();
		break;
	case 2:
		BeginStaffArea();
		break;
	default:
		break;
	}
}

void USkillComponent::PlaySkill_E()
{
	switch (CurrentWeaponType)
	{
	case 0:
		BeginSwordParrying();
		break;
	case 1:
		BeginBowBackstep();
		break;
	case 2:
		BeginStaffUpGround();
		break;
	default:
		break;
	}
}

void USkillComponent::PlaySkill_R()
{
	switch (CurrentWeaponType)
	{
	case 0:
		BeginSwordAura();
		break;
	case 1:
		BeginBowAutoTargeting();
		break;
	case 2:
		BeginStaffThunderbolt();
		break;
	default:
		break;
	}
}

void USkillComponent::SetWeaponType(int32& InCurrentWeaponType)
{
	CurrentWeaponType = InCurrentWeaponType;
	UE_LOG(LogTemp, Display, TEXT("Current Weapon Type : %d"), CurrentWeaponType);
}

void USkillComponent::BeginSwordSting()
{
	UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();

	Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	AnimInstance->Montage_Play(SkillMontageData->SwordMontages[0]);

	FOnMontageEnded MontageEnd;
	MontageEnd.BindUObject(this, &USkillComponent::EndSwordSting);
	AnimInstance->Montage_SetEndDelegate(MontageEnd, SkillMontageData->SwordMontages[0]);
}

void USkillComponent::EndSwordSting(UAnimMontage* Target, bool IsProperlyEnded)
{
	Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void USkillComponent::BeginSwordWhirlwind()
{
	UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();

	Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	AnimInstance->Montage_Play(SkillMontageData->SwordMontages[1]);

	FOnMontageEnded MontageEnd;
	MontageEnd.BindUObject(this, &USkillComponent::EndSwordWhirlwind);
	AnimInstance->Montage_SetEndDelegate(MontageEnd, SkillMontageData->SwordMontages[1]);
}

void USkillComponent::EndSwordWhirlwind(UAnimMontage* Target, bool IsProperlyEnded)
{
	Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void USkillComponent::BeginSwordParrying()
{
	UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();

	Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	AnimInstance->Montage_Play(SkillMontageData->SwordMontages[2]);

	FOnMontageEnded MontageEnd;
	MontageEnd.BindUObject(this, &USkillComponent::EndSwordParrying);
	AnimInstance->Montage_SetEndDelegate(MontageEnd, SkillMontageData->SwordMontages[2]);
}

void USkillComponent::EndSwordParrying(UAnimMontage* Target, bool IsProperlyEnded)
{
	Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void USkillComponent::BeginSwordAura()
{
	UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();

	Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	AnimInstance->Montage_Play(SkillMontageData->SwordMontages[3], 3.0f);

	FOnMontageEnded MontageEnd;
	MontageEnd.BindUObject(this, &USkillComponent::EndSwordAura);
	AnimInstance->Montage_SetEndDelegate(MontageEnd, SkillMontageData->SwordMontages[3]);
}

void USkillComponent::EndSwordAura(UAnimMontage* Target, bool IsProperlyEnded)
{
	Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void USkillComponent::BeginBowSeveralArrows()
{
}

void USkillComponent::EndBowSeveralArrows(UAnimMontage* Target, bool IsProperlyEnded)
{
}

void USkillComponent::BeginBowExplosionArrow()
{
}

void USkillComponent::EndBowExplosionArrow(UAnimMontage* Target, bool IsProperlyEnded)
{
}

void USkillComponent::BeginBowBackstep()
{
}

void USkillComponent::EndBowBackstep(UAnimMontage* Target, bool IsProperlyEnded)
{
}

void USkillComponent::BeginBowAutoTargeting()
{
}

void USkillComponent::EndBowAutoTargeting(UAnimMontage* Target, bool IsProperlyEnded)
{
}

void USkillComponent::BeginStaffFireball()
{
}

void USkillComponent::EndStaffFireball(UAnimMontage* Target, bool IsProperlyEnded)
{
}

void USkillComponent::BeginStaffArea()
{
}

void USkillComponent::EndStaffArea(UAnimMontage* Target, bool IsProperlyEnded)
{
}

void USkillComponent::BeginStaffUpGround()
{
}

void USkillComponent::EndStaffUpGround(UAnimMontage* Target, bool IsProperlyEnded)
{
}

void USkillComponent::BeginStaffThunderbolt()
{
}

void USkillComponent::EndStaffThunderbolt(UAnimMontage* Target, bool IsProperlyEnded)
{
}


