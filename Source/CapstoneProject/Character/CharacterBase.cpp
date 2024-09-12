// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Player/CPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Stat/CharacterStatComponent.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "Character/CharacterComboAttackData.h"
#include "Weapon/Sword.h"
#include "Weapon/Bow.h"
#include "Weapon/Staff.h"
#include "UI/WeaponChoiceUI.h"
#include "SkillHeader/SkillHeader.h"

ACharacterBase::ACharacterBase()
{
	/* 쿼터뷰 시점을 위한 속성값 */
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);

	/* 카메라 컴포넌트 부착 */
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetUsingAbsoluteRotation(true);
	SpringArm->bUsePawnControlRotation = false;
	SpringArm->bDoCollisionTest = false;
	SpringArm->TargetArmLength = 800.f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;

	/* Enhanced Input 로딩 */
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContextRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/No-Face/Input/InputMappingContext/IMC_Default.IMC_Default'"));
	if (InputMappingContextRef.Object)
	{
		InputMappingContext = InputMappingContextRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> RightClickActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/No-Face/Input/InputAction/IA_RightClick.IA_RightClick'"));
	if (RightClickActionRef.Object)
	{
		RightClickAction = RightClickActionRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> Q_SkillActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/No-Face/Input/InputAction/IA_Q.IA_Q'"));
	if (Q_SkillActionRef.Object)
	{
		Q_SkillAction = Q_SkillActionRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> W_SkillActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/No-Face/Input/InputAction/IA_W.IA_W'"));
	if (W_SkillActionRef.Object)
	{
		W_SkillAction = W_SkillActionRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> E_SkillActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/No-Face/Input/InputAction/IA_E.IA_E'"));
	if (E_SkillActionRef.Object)
	{
		E_SkillAction = E_SkillActionRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> R_SkillActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/No-Face/Input/InputAction/IA_R.IA_R'"));
	if (R_SkillActionRef.Object)
	{
		R_SkillAction = R_SkillActionRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> LeftClickActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/No-Face/Input/InputAction/IA_LeftClick.IA_LeftClick'"));
	if (LeftClickActionRef.Object)
	{
		LeftClickAction = LeftClickActionRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> NextWeaponActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/No-Face/Input/InputAction/IA_NextWeapon.IA_NextWeapon'"));
	if (NextWeaponActionRef.Object)
	{
		NextWeaponAction = NextWeaponActionRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> PrevWeaponActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/No-Face/Input/InputAction/IA_PrevWeapon.IA_PrevWeapon'"));
	if (PrevWeaponActionRef.Object)
	{
		PrevWeaponAction = PrevWeaponActionRef.Object;
	}
	
	/* Mesh */
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MainMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Manny.SKM_Manny'"));
	if (MainMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(MainMeshRef.Object);
	}

	/* 애니메이션 */
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);


	/* 스텟 */
	Stat = CreateDefaultSubobject<UCharacterStatComponent>(TEXT("Stat"));

	/* 무기 */
	TakeItemDelegateArray.Add(FTakeItemDelegateWrapper(FTakeItemDelegate::CreateUObject(this, &ACharacterBase::EquipSword)));
	TakeItemDelegateArray.Add(FTakeItemDelegateWrapper(FTakeItemDelegate::CreateUObject(this, &ACharacterBase::EquipBow)));
	TakeItemDelegateArray.Add(FTakeItemDelegateWrapper(FTakeItemDelegate::CreateUObject(this, &ACharacterBase::EquipStaff)));
	
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}

	//초반에 칼들고 시작
	EquipSword();
}

void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	
	EnhancedInputComponent->BindAction(RightClickAction, ETriggerEvent::Started, this, &ACharacterBase::OnClickStart);
	EnhancedInputComponent->BindAction(RightClickAction, ETriggerEvent::Triggered, this, &ACharacterBase::OnClicking);
	EnhancedInputComponent->BindAction(RightClickAction, ETriggerEvent::Completed, this, &ACharacterBase::OnRelease);
	EnhancedInputComponent->BindAction(LeftClickAction, ETriggerEvent::Started, this, &ACharacterBase::OnAttackStart);
	EnhancedInputComponent->BindAction(Q_SkillAction, ETriggerEvent::Started, this, &ACharacterBase::Q_Skill);
	EnhancedInputComponent->BindAction(W_SkillAction, ETriggerEvent::Started, this, &ACharacterBase::W_Skill);
	EnhancedInputComponent->BindAction(E_SkillAction, ETriggerEvent::Started, this, &ACharacterBase::E_Skill);
	EnhancedInputComponent->BindAction(R_SkillAction, ETriggerEvent::Started, this, &ACharacterBase::R_Skill);
	EnhancedInputComponent->BindAction(NextWeaponAction, ETriggerEvent::Started, this, &ACharacterBase::NextWeapon);
	EnhancedInputComponent->BindAction(PrevWeaponAction, ETriggerEvent::Started, this, &ACharacterBase::PrevWeapon);
	
}

void ACharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	CurrentWeaponType = EWeaponType::Sword;

	SwordSkillArray.Add(NewObject<USkill_Q_Sword>(this));
	SwordSkillArray.Add(NewObject<USkill_W_Sword>(this));
	SwordSkillArray.Add(NewObject<USkill_E_Sword>(this));
	SwordSkillArray.Add(NewObject<USkill_R_Sword>(this));
	BowSkillArray.Add(NewObject<USkill_Q_Bow>(this));
	BowSkillArray.Add(NewObject<USkill_W_Bow>(this));
	BowSkillArray.Add(NewObject<USkill_E_Bow>(this));
	BowSkillArray.Add(NewObject<USkill_R_Bow>(this));
	StaffSkillArray.Add(NewObject<USkill_Q_Staff>(this));
	StaffSkillArray.Add(NewObject<USkill_W_Staff>(this));
	StaffSkillArray.Add(NewObject<USkill_E_Staff>(this));
	StaffSkillArray.Add(NewObject<USkill_R_Staff>(this));

	Skills.Add(EWeaponType::Sword, SwordSkillArray);
	Skills.Add(EWeaponType::Bow, BowSkillArray);
	Skills.Add(EWeaponType::Staff, StaffSkillArray);
}

float ACharacterBase::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	
	Stat->ApplyDamage(Damage);

	return 0.0f;
}

void ACharacterBase::Q_Skill()
{
	UE_LOG(LogTemp, Display, TEXT("Base Q Skill"));
	Skills[CurrentWeaponType][0]->ExecuteSkill();
}

void ACharacterBase::W_Skill()
{
	UE_LOG(LogTemp, Display, TEXT("Base W Skill"));
	Skills[CurrentWeaponType][1]->ExecuteSkill();
}

void ACharacterBase::E_Skill()
{
	UE_LOG(LogTemp, Display, TEXT("Base E Skill"));
	Skills[CurrentWeaponType][2]->ExecuteSkill();
}

void ACharacterBase::R_Skill()
{
	UE_LOG(LogTemp, Display, TEXT("Base R Skill"));
	Skills[CurrentWeaponType][3]->ExecuteSkill();
}

void ACharacterBase::OnClickStart()
{
	GetController()->StopMovement();
}

void ACharacterBase::OnClicking()
{
	ACPlayerController* PC = GetPlayerController();
	ensure(PC);

	FHitResult ClickedLocation;
	bool bHit = PC->GetHitResultUnderCursor(ECC_Visibility, true, ClickedLocation);
	if (bHit)
	{
		CachedLocation = ClickedLocation.Location;
	}

	FVector WorldDirection = (CachedLocation - GetActorLocation()).GetSafeNormal();
	AddMovementInput(WorldDirection);
}

void ACharacterBase::OnRelease()
{
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), CachedLocation);
}

void ACharacterBase::OnAttackStart()
{
	if (TraceAttack() == false)
	{
		return;
	}

	if (CurrentCombo == 0)
	{
		OnClickStart();
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

bool ACharacterBase::TraceAttack()
{
	return GetPlayerController()->GetHitResultUnderCursor(ECC_Visibility, true, AttackHitResult);
}

void ACharacterBase::BeginDefaultAttack()
{
	CurrentCombo = 1;
	RotateToTarget();

	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(DefaultAttackMontage);

	FOnMontageEnded MontageEnded;
	MontageEnded.BindUObject(this, &ACharacterBase::EndDefaultAttack);
	AnimInstance->Montage_SetEndDelegate(MontageEnded, DefaultAttackMontage);
	
	ComboTimer.Invalidate();
	SetComboTimer();
}

void ACharacterBase::EndDefaultAttack(UAnimMontage* Target, bool IsProperlyEnded)
{
	ensure(CurrentCombo != 0);
	CurrentCombo = 0;
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void ACharacterBase::SetComboTimer()
{
	int32 ComboIndex = CurrentCombo - 1;
	ensure(ComboData->EffectiveFrameCount.IsValidIndex(ComboIndex));

	float ComboEffectiveTime = (ComboData->EffectiveFrameCount[ComboIndex] / ComboData->FrameRate);
	if (ComboEffectiveTime > 0.0f)
	{
		GetWorld()->GetTimerManager().SetTimer(ComboTimer, this, &ACharacterBase::CheckCombo, ComboEffectiveTime, false);
	}
}

void ACharacterBase::CheckCombo()
{
	ComboTimer.Invalidate();
	if (HasNextComboCommand)
	{
		RotateToTarget();

		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

		CurrentCombo = FMath::Clamp(CurrentCombo + 1, 1, ComboData->MaxComboCount);
		FName NextSection = *FString::Printf(TEXT("%s%d"), *ComboData->MontageSectionNamePrefix, CurrentCombo);
		AnimInstance->Montage_JumpToSection(NextSection, DefaultAttackMontage);
		SetComboTimer();
		HasNextComboCommand = false;
	}
}

void ACharacterBase::RotateToTarget()
{
	if (RotateTimer.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(RotateTimer);
	}

	GetWorld()->GetTimerManager().SetTimer(RotateTimer, this, &ACharacterBase::UpdateRotate, 0.01f, true);

}

void ACharacterBase::UpdateRotate()
{
	FRotator TargetRotation = (AttackHitResult.Location - GetActorLocation()).Rotation();
	TargetRotation.Pitch = 0;
	SetActorRelativeRotation(FMath::RInterpTo(GetActorRotation(), TargetRotation, GetWorld()->GetDeltaSeconds(), 15.0f));

	if (FMath::Abs((TargetRotation - GetActorRotation()).Yaw) < 5.0f)
	{
		GetWorld()->GetTimerManager().ClearTimer(RotateTimer);
	}
}

void ACharacterBase::NextWeapon()
{
	WeaponIndex += 1;
	if (WeaponIndex > 2)
	{
		WeaponIndex = 0;
	}

	TakeItemDelegateArray[WeaponIndex].TakeItemDelegate.ExecuteIfBound();
	CurrentWeaponType = static_cast<EWeaponType>(WeaponIndex);
}

void ACharacterBase::PrevWeapon()
{
	WeaponIndex -= 1;
	if (WeaponIndex < 0)
	{
		WeaponIndex = 2;
	}

	TakeItemDelegateArray[WeaponIndex].TakeItemDelegate.ExecuteIfBound();
	CurrentWeaponType = static_cast<EWeaponType>(WeaponIndex);
}

void ACharacterBase::EquipSword()
{
	UE_LOG(LogTemp, Display, TEXT("Equip Sword"));

	if (WeaponBase)
	{
		WeaponBase->Destroy();
	}
	
	FVector SpawnLocation = GetMesh()->GetSocketLocation(TEXT("hand_rSocket"));
	FRotator SpawnRotation = GetMesh()->GetSocketRotation(TEXT("hand_rSocket"));

	WeaponBase = GetWorld()->SpawnActor<ASword>(SwordClass, SpawnLocation, SpawnRotation);
	WeaponBase->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("hand_rSocket"));
}

void ACharacterBase::EquipBow()
{
	UE_LOG(LogTemp, Display, TEXT("Equip Bow"));

	if (WeaponBase)
	{
		WeaponBase->Destroy();
	}

	FVector SpawnLocation = GetMesh()->GetSocketLocation(TEXT("hand_rSocket"));
	FRotator SpawnRotation = GetMesh()->GetSocketRotation(TEXT("hand_rSocket"));

	WeaponBase = GetWorld()->SpawnActor<ABow>(BowClass, SpawnLocation, SpawnRotation);
	WeaponBase->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("hand_rSocket"));
}

void ACharacterBase::EquipStaff()
{
	UE_LOG(LogTemp, Display, TEXT("Equip Staff"));

	if (WeaponBase)
	{
		WeaponBase->Destroy();
	}

	FVector SpawnLocation = GetMesh()->GetSocketLocation(TEXT("hand_rSocket"));
	FRotator SpawnRotation = GetMesh()->GetSocketRotation(TEXT("hand_rSocket"));

	WeaponBase = GetWorld()->SpawnActor<AStaff>(StaffClass, SpawnLocation, SpawnRotation);
	WeaponBase->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("hand_rSocket"));
}

ACPlayerController* ACharacterBase::GetPlayerController() const
{
	return Cast<ACPlayerController>(GetController());
}

