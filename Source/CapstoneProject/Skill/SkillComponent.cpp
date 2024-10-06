// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillComponent.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/CharacterSkillMontageData.h"
#include "Kismet/GameplayStatics.h"
#include "Enemy/EnemyBase.h"
#include "Skill/StaffMeteor.h"
#include "Skill/StaffArea.h"
#include "Skill/StaffUpGround.h"
#include "Skill/StaffThunderbolt.h"
#include "Weapon/Arrow.h"
#include "Engine/DamageEvents.h"

USkillComponent::USkillComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void USkillComponent::BeginPlay()
{
	Super::BeginPlay();

	Character = CastChecked<ACharacter>(GetOwner());
	PlayerController = CastChecked<APlayerController>(Character->GetController());
}

void USkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bCasting)
	{
		//Cursor가 멤버변수니까 해당 위치 정보를 가지고 각 스킬 함수에서 Cursor의 위치를 참조하여 시전 범위를 생성하면됨.
		PlayerController->GetHitResultUnderCursor(ECC_Visibility, true, Cursor);
		DrawDebugSphere(GetWorld(), Cursor.Location, 20.f, 32, FColor::Red, false);
	}
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
		BeginStaffMeteor();
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
		BeginBowOneShot();
		break;
	case 2:
		BeginStaffThunderbolt();
		break;
	default:
		break;
	}
}

void USkillComponent::SetWeaponType(const int32& InCurrentWeaponType)
{
	CurrentWeaponType = InCurrentWeaponType;
}

void USkillComponent::BeginSwordSting()
{
	if (!bCanUseSkill_Sword_Q) return;
	else StartCooldown(CooldownDuration_Sword_Q, CooldownTimerHandle_Sword_Q, bCanUseSkill_Sword_Q);

	UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();

	bCanChangeWeapon = false;
	Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	AnimInstance->Montage_Play(SkillMontageData->SwordMontages[0], 1.0f);

	FOnMontageEnded MontageEnd;
	MontageEnd.BindUObject(this, &USkillComponent::EndSwordSting);
	AnimInstance->Montage_SetEndDelegate(MontageEnd, SkillMontageData->SwordMontages[0]);
}

void USkillComponent::EndSwordSting(UAnimMontage* Target, bool IsProperlyEnded)
{
	Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	bCanChangeWeapon = true;
}

void USkillComponent::BeginSwordWhirlwind()
{
	if (!bCanUseSkill_Sword_W) return;	
	else StartCooldown(CooldownDuration_Sword_W, CooldownTimerHandle_Sword_W, bCanUseSkill_Sword_W);
	
	UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();

	bCanChangeWeapon = false;
	Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	AnimInstance->Montage_Play(SkillMontageData->SwordMontages[1], 1.0f);

	FOnMontageEnded MontageEnd;
	MontageEnd.BindUObject(this, &USkillComponent::EndSwordWhirlwind);
	AnimInstance->Montage_SetEndDelegate(MontageEnd, SkillMontageData->SwordMontages[1]);
}

void USkillComponent::EndSwordWhirlwind(UAnimMontage* Target, bool IsProperlyEnded)
{
	Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	bCanChangeWeapon = true;
}

void USkillComponent::BeginSwordParrying()
{
	if (!bCanUseSkill_Sword_E) return;
	else StartCooldown(CooldownDuration_Sword_E, CooldownTimerHandle_Sword_E, bCanUseSkill_Sword_E);

	UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();

	bCanChangeWeapon = false;
	Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	AnimInstance->Montage_Play(SkillMontageData->SwordMontages[2], 1.0f);

	//애니메이션의 시작과 끝이 패링 타이밍, Notify 를 사용해 타이밍을 조정할 필요가 있음
	ParryingSign.ExecuteIfBound();

	FOnMontageEnded MontageEnd;
	MontageEnd.BindUObject(this, &USkillComponent::EndSwordParrying);
	AnimInstance->Montage_SetEndDelegate(MontageEnd, SkillMontageData->SwordMontages[2]);
}

void USkillComponent::EndSwordParrying(UAnimMontage* Target, bool IsProperlyEnded)
{
	Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	ParryingSign.ExecuteIfBound();
	bCanChangeWeapon = true;
}

void USkillComponent::ParryingSuccess(AActor* Attacker)
{
	if (AEnemyBase* Enemy = Cast<AEnemyBase>(Attacker))
	{
		Enemy->Stun();
		//반격 애니메이션 혹은 추가 공격;
	}
}

void USkillComponent::BeginSwordAura()
{
	if (!bCanUseSkill_Sword_R) return;
	else StartCooldown(CooldownDuration_Sword_R, CooldownTimerHandle_Sword_R, bCanUseSkill_Sword_R);

	UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();

	bCanChangeWeapon = false;
	Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	AnimInstance->Montage_Play(SkillMontageData->SwordMontages[3], 3.0f);

	FOnMontageEnded MontageEnd;
	MontageEnd.BindUObject(this, &USkillComponent::EndSwordAura);
	AnimInstance->Montage_SetEndDelegate(MontageEnd, SkillMontageData->SwordMontages[3]);
}

void USkillComponent::EndSwordAura(UAnimMontage* Target, bool IsProperlyEnded)
{
	Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	bCanChangeWeapon = true;
}

void USkillComponent::BeginBowSeveralArrows()
{
	if (!bCanUseSkill_Bow_Q) return;
	else StartCooldown(CooldownDuration_Bow_Q, CooldownTimerHandle_Bow_Q, bCanUseSkill_Bow_Q);

	UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();

	bCanChangeWeapon = false;
	Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	AnimInstance->Montage_Play(SkillMontageData->BowMontages[0]);

	FOnMontageEnded MontageEnd;
	MontageEnd.BindUObject(this, &USkillComponent::EndBowSeveralArrows);
	AnimInstance->Montage_SetEndDelegate(MontageEnd, SkillMontageData->BowMontages[0]);
}

void USkillComponent::EndBowSeveralArrows(UAnimMontage* Target, bool IsProperlyEnded)
{
	Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	bCanChangeWeapon = true;
}

void USkillComponent::BeginBowExplosionArrow()
{
	UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();
	bCanChangeWeapon = false;

	if (bCasting)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), RainArrows, Cursor.Location, FRotator::ZeroRotator);
		UGameplayStatics::ApplyRadialDamage(GetOwner(), 50.f, Cursor.Location, 200.f, UDamageType::StaticClass(), TArray<AActor*>(), GetOwner());

		bCasting = false;

		if (!AnimInstance->Montage_IsPlaying(SkillMontageData->BowMontages[1]))
		{
			AnimInstance->Montage_Resume(SkillMontageData->BowMontages[1]);
		}
		//else 사용자가 입력을 너무 빨리 했을 때 처리 해야함

		FOnMontageEnded MontageEnd;
		MontageEnd.BindUObject(this, &USkillComponent::EndBowExplosionArrow);
		AnimInstance->Montage_SetEndDelegate(MontageEnd, SkillMontageData->BowMontages[1]);
	}
	else
	{
		if (!bCanUseSkill_Bow_W) return;
		else StartCooldown(CooldownDuration_Bow_W, CooldownTimerHandle_Bow_W, bCanUseSkill_Bow_W);

		bCasting = true;

		SkillQueue.Enqueue([this]()
			{
				BeginBowExplosionArrow();
			});

		Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
		AnimInstance->Montage_Play(SkillMontageData->BowMontages[1], 1.0f);
	}
}

void USkillComponent::EndBowExplosionArrow(UAnimMontage* Target, bool IsProperlyEnded)
{
	Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	bCanChangeWeapon = true;
}

void USkillComponent::BeginBowBackstep()
{
	if (!bCanUseSkill_Bow_E) return;
	else StartCooldown(CooldownDuration_Bow_E, CooldownTimerHandle_Bow_E, bCanUseSkill_Bow_E);

	UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();

	bCanChangeWeapon = false;
	AnimInstance->Montage_Play(SkillMontageData->BowMontages[2], 4.f);

	FVector BackstepDirection = Character->GetActorForwardVector() * -500.f;
	Character->LaunchCharacter(BackstepDirection + FVector(0.f, 0.f, 100.f), true, true);

	FOnMontageEnded MontageEnd;
	MontageEnd.BindUObject(this, &USkillComponent::EndBowBackstep);
	AnimInstance->Montage_SetEndDelegate(MontageEnd, SkillMontageData->BowMontages[2]);
}

void USkillComponent::EndBowBackstep(UAnimMontage* Target, bool IsProperlyEnded)
{
	bCanChangeWeapon = true;
}

/* 애니메이션이 천천히 실행되고, 카메라가 줌이 되는 효과 추가 하자 */
void USkillComponent::BeginBowOneShot()
{
	if (!bCanUseSkill_Bow_R) return;
	else StartCooldown(CooldownDuration_Bow_R, CooldownTimerHandle_Bow_R, bCanUseSkill_Bow_R);

	UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();

	bCanChangeWeapon = false;
	Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	AnimInstance->Montage_Play(SkillMontageData->BowMontages[3]);
	
	FOnMontageEnded MontageEnd;
	MontageEnd.BindUObject(this, &USkillComponent::EndBowOneShot);
	AnimInstance->Montage_SetEndDelegate(MontageEnd, SkillMontageData->BowMontages[3]);
}

void USkillComponent::EndBowOneShot(UAnimMontage* Target, bool IsProperlyEnded)
{
	FireOneShot();

	Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	bCanChangeWeapon = true;
}

void USkillComponent::FireOneShot()
{
	TArray<FHitResult> HitResults;

	const float Damage = 100.f;
	const float Range = 500.f;
	FVector Origin = Character->GetActorLocation();
	FVector End = Origin + (Character->GetActorForwardVector() * Range);

	FVector ForwardVector = Character->GetActorForwardVector() * Range;
	FQuat RootRot = FRotationMatrix::MakeFromZ(ForwardVector).ToQuat();
	FVector BoxExtent = FVector(100.f, 100.f, 100.f);
	FCollisionQueryParams Params(NAME_None, true, Character);

	bool bHit = GetWorld()->SweepMultiByChannel(HitResults, Origin, End, RootRot, ECC_GameTraceChannel2, FCollisionShape::MakeBox(BoxExtent), Params);
	if (bHit)
	{
		FDamageEvent DamageEvent;
		for (const auto& HitResult : HitResults)
		{
			UE_LOG(LogTemp, Display, TEXT("HitResult Actor Name : %s"), *HitResult.GetActor()->GetActorNameOrLabel());
			HitResult.GetActor()->TakeDamage(Damage, DamageEvent, PlayerController, Character);
		}
	}

	DrawDebugBox(GetWorld(), Origin, BoxExtent, RootRot, FColor::Green, false, 5.f);
	DrawDebugBox(GetWorld(), End, BoxExtent, RootRot, FColor::Green, false, 5.f);
}

void USkillComponent::Bow_Q_Skill()
{
	FVector ForwardVector = Character->GetActorForwardVector();

	for (int32 Degree = -60; Degree <= 60; Degree += 20)
	{
		FVector SpawnVector = ForwardVector.RotateAngleAxis(Degree, FVector::UpVector);

		FVector SpawnLocation = Character->GetActorLocation() + FVector(10.f, 0.f, 0.f);
		FRotator SpawnRotator = SpawnVector.Rotation();

		AArrow* Arrow = GetWorld()->SpawnActor<AArrow>(ArrowClass, SpawnLocation, SpawnRotator);
		Arrow->SetOwner(Character);
		Arrow->Init(SpawnVector, SpawnLocation, SpawnRotator);
	}
}

void USkillComponent::Bow_W_Skill()
{
	UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();
	if (AnimInstance->Montage_IsPlaying(SkillMontageData->BowMontages[1]))
	{
		AnimInstance->Montage_Pause(SkillMontageData->BowMontages[1]);
	}
}

void USkillComponent::BeginStaffMeteor()
{
	if (bCasting)
	{
		//수정중 
		/*FVector SpawnLocation = Character->GetActorLocation() + FVector(0.f, 0.f, 150.f);
		FRotator SpawnRotation = Character->GetActorRotation();
		AStaffMeteor* Meteor = GetWorld()->SpawnActor<AStaffMeteor>(MeteorClass, SpawnLocation, SpawnRotation);
		Meteor->Init(Cursor.Location);*/
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MeteorEffect, Cursor.Location + FVector(0.f, 0.f, 500.f), FRotator::ZeroRotator);
		UGameplayStatics::ApplyRadialDamage(GetOwner(), 50.f, Cursor.Location, 200.f, UDamageType::StaticClass(), TArray<AActor*>(), GetOwner());


		bCasting = false;
	}
	else
	{
		if (!bCanUseSkill_Staff_Q) return;
		else StartCooldown(CooldownDuration_Staff_Q, CooldownTimerHandle_Staff_Q, bCanUseSkill_Staff_Q);

		bCasting = true;
		
		//컨테이너에 람다형식으로 함수 등록
		SkillQueue.Enqueue([this]() {
			BeginStaffMeteor();
        });
	}
}

void USkillComponent::EndStaffMeteor(UAnimMontage* Target, bool IsProperlyEnded)
{
}

void USkillComponent::BeginStaffArea()
{
	if (bCasting)
	{
		FVector SpawnLocation = Cursor.Location;
		FRotator SpawnRotation = Character->GetActorRotation();
		AStaffArea* Area = GetWorld()->SpawnActor<AStaffArea>(AreaClass, SpawnLocation, SpawnRotation);
		Area->SetOwner(Character);

		bCasting = false;
	}
	else
	{
		if (!bCanUseSkill_Staff_W) return;
		else StartCooldown(CooldownDuration_Staff_W, CooldownTimerHandle_Staff_W, bCanUseSkill_Staff_W);

		bCasting = true;

		//컨테이너에 람다형식으로 함수 등록
		SkillQueue.Enqueue([this]()
			{
				BeginStaffArea();
			});
	}
}

void USkillComponent::EndStaffArea(UAnimMontage* Target, bool IsProperlyEnded)
{
}

void USkillComponent::BeginStaffUpGround()
{
	if (bCasting)
	{
		FVector SpawnLocation = Cursor.Location;
		FRotator SpawnRotation = Character->GetActorRotation();
		AStaffUpGround* UpGround = GetWorld()->SpawnActor<AStaffUpGround>(UpGroundClass, SpawnLocation, SpawnRotation);
		UpGround->SetOwner(Character);
		UpGround->ActiveGroundUp();

		bCasting = false;
	}
	else
	{
		if (!bCanUseSkill_Staff_E) return;
		else StartCooldown(CooldownDuration_Staff_E, CooldownTimerHandle_Staff_E, bCanUseSkill_Staff_E);

		bCasting = true;

		//컨테이너에 람다형식으로 함수 등록
		SkillQueue.Enqueue([this]()
			{
				BeginStaffUpGround();
			});
	}
}

void USkillComponent::EndStaffUpGround(UAnimMontage* Target, bool IsProperlyEnded)
{
}

void USkillComponent::BeginStaffThunderbolt()
{
	if (!bCanUseSkill_Staff_R) return;
	else StartCooldown(CooldownDuration_Staff_R, CooldownTimerHandle_Staff_R, bCanUseSkill_Staff_R);

	FVector SpawnLocation = Character->GetMesh()->GetSocketLocation(TEXT("root")) + FVector(0.f, 0.f, 5.f);
	FRotator SpawnRotation = Character->GetActorRotation();
	AStaffThunderbolt* Thunderbolt = GetWorld()->SpawnActor<AStaffThunderbolt>(ThunderboltClass, SpawnLocation, SpawnRotation);
	Thunderbolt->SetOwner(Character);
	Thunderbolt->ActiveThunderbolt();
}

void USkillComponent::EndStaffThunderbolt(UAnimMontage* Target, bool IsProperlyEnded)
{
}

void USkillComponent::StartCooldown(float CooldownDuration, FTimerHandle& CooldownTimerHandle, bool& bCanUseSkill)
{
	bCanUseSkill = false;
	GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandle, 
		[&]()
		{
			bCanUseSkill = true;
		}, CooldownDuration, false);
}



