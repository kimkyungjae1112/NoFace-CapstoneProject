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
#include "Animation/CharacterAnimInstance.h"
#include "Animation/AnimMontage.h"
#include "Character/CharacterComboAttackData.h"
#include "Weapon/Sword.h"
#include "Weapon/Bow.h"
#include "Weapon/Staff.h"
#include "Skill/SkillComponent.h"
#include "Character/CharacterHitCheckComponent.h"
#include "Character/CharacterDefaultAttackComponent.h"
#include "Interface/BowInterface.h"
#include "Components/CapsuleComponent.h"
#include "Interface/PlayerHUDInterface.h"
#include "UI/HUDWidget.h"

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
	SpringArm->TargetArmLength = 1000.f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;

	/* 콜리전 설정 */
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));

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
	static ConstructorHelpers::FObjectFinder<UInputAction> CancelActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/No-Face/Input/InputAction/IA_Cancel.IA_Cancel'"));
	if (CancelActionRef.Object)
	{
		CancelAction = CancelActionRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> ZoomInOutActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/No-Face/Input/InputAction/IA_ZoomInOut.IA_ZoomInOut'"));
	if (ZoomInOutActionRef.Object)
	{
		ZoomInOutAction = ZoomInOutActionRef.Object;
	}
	
	/* Mesh */
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MainMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/No-Face/Character/Mesh/SKM_Quinn_Simple.SKM_Quinn_Simple'"));
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

	/* 컴포넌트 */
	SkillComponent = CreateDefaultSubobject<USkillComponent>(TEXT("Skill"));
	SkillComponent->ParryingSign.BindUObject(this, &ACharacterBase::ToggleParrying);

	HitCheckComponent = CreateDefaultSubobject<UCharacterHitCheckComponent>(TEXT("Hit Checker"));

	AttackComponent = CreateDefaultSubobject<UCharacterDefaultAttackComponent>(TEXT("Attack"));

	/* 태그 */
	Tags.Add(TEXT("Player"));
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
	CurrentWeaponType = EWeaponType::Sword;
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
	EnhancedInputComponent->BindAction(ZoomInOutAction, ETriggerEvent::Triggered, this, &ACharacterBase::ZoomInOut);

	EnhancedInputComponent->BindAction(CancelAction, ETriggerEvent::Started, this, &ACharacterBase::CancelCasting);
}

float ACharacterBase::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	
	if (bIsParrying)
	{
		SkillComponent->ParryingSuccess(DamageCauser);
		return 0.f;
	}

	Stat->ApplyDamage(Damage);

	return Damage;
}

int ACharacterBase::GetWeaponType()
{
	return WeaponIndex;
}

void ACharacterBase::Q_Skill()
{
	RotateToTarget();
	OnClickStart();
	SkillComponent->PlaySkill_Q();
}

void ACharacterBase::W_Skill()
{
	RotateToTarget();
	OnClickStart();
	SkillComponent->PlaySkill_W();
}

void ACharacterBase::E_Skill()
{
	RotateToTarget();
	OnClickStart();
	SkillComponent->PlaySkill_E();
}

void ACharacterBase::R_Skill()
{
	RotateToTarget();
	OnClickStart();
	SkillComponent->PlaySkill_R();
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

	/* 스킬 캐스팅 중이면 해당 스킬 싱행 */
	if (SkillComponent->GetCastingFlag())
	{
		TFunction<void()> SkillAction;
		if (SkillComponent->SkillQueue.Dequeue(SkillAction))
		{
			RotateToTarget();
			SkillAction();
			return;
		}
	}

	OnClickStart();
	RotateToTarget();
	AttackComponent->BeginAttack();
}

bool ACharacterBase::TraceAttack()
{
	return GetPlayerController()->GetHitResultUnderCursor(ECC_Visibility, true, AttackHitResult);
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
	FHitResult TargetHitResult;
	bool bHit = GetPlayerController()->GetHitResultUnderCursor(ECC_Visibility, true, TargetHitResult);

	FRotator TargetRotation = (TargetHitResult.Location - GetActorLocation()).Rotation();
	TargetRotation.Pitch = 0;
	SetActorRelativeRotation(FMath::RInterpTo(GetActorRotation(), TargetRotation, GetWorld()->GetDeltaSeconds(), 20.0f));

	if (FMath::Abs((TargetRotation - GetActorRotation()).Yaw) < 1.0f)
	{
		GetWorld()->GetTimerManager().ClearTimer(RotateTimer);
	}
}

void ACharacterBase::ZoomInOut(const FInputActionValue& Value)
{
	const float WheelValue = Value.Get<float>() * -50.f;

	SpringArm->TargetArmLength = FMath::Clamp(SpringArm->TargetArmLength + WheelValue, 200.f, 1200.f);
}

void ACharacterBase::CancelCasting()
{
	/* 스킬 캐스팅 중 취소 */
	if (SkillComponent->GetCastingFlag())
	{
		SkillComponent->SetCastingFlag(false);
		SkillComponent->SkillQueue.Pop();

		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		AnimInstance->StopAllMontages(0.1f);

		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	}
}

void ACharacterBase::NextWeapon()
{
	if (!AttackComponent->CanChangeWeapon() || !SkillComponent->CanChangeWeapon())
	{
		return;
	}

	WeaponIndex += 1;
	if (WeaponIndex > 2)
	{
		WeaponIndex = 0;
	}

	ChangeWeapon();
	AnimWeaponIndex();
}

void ACharacterBase::PrevWeapon()
{
	if (!AttackComponent->CanChangeWeapon() || !SkillComponent->CanChangeWeapon())
	{
		return;
	}

	WeaponIndex -= 1;
	if (WeaponIndex < 0)
	{
		WeaponIndex = 2;
	}
	
	ChangeWeapon();
	AnimWeaponIndex();
}

void ACharacterBase::AnimWeaponIndex()
{
	UCharacterAnimInstance* AnimInstance = Cast<UCharacterAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance)
	{
		AnimInstance->WeaponIndex = WeaponIndex;
	}
}

void ACharacterBase::ChangeWeapon()
{
	SkillComponent->SetWeaponType(WeaponIndex);
	AttackComponent->SetWeaponType(WeaponIndex);
	TakeItemDelegateArray[WeaponIndex].TakeItemDelegate.ExecuteIfBound();
	CurrentWeaponType = static_cast<EWeaponType>(WeaponIndex);
}

void ACharacterBase::EquipSword()
{
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
	if (WeaponBase)
	{
		WeaponBase->Destroy();
	}

	FVector SpawnLocation = GetMesh()->GetSocketLocation(TEXT("hand_lSocket_Bow"));
	FRotator SpawnRotation = GetMesh()->GetSocketRotation(TEXT("hand_lSocket_Bow"));

	WeaponBase = GetWorld()->SpawnActor<ABow>(BowClass, SpawnLocation, SpawnRotation);
	WeaponBase->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("hand_lSocket_Bow"));
	IBowInterface* Interface = Cast<IBowInterface>(AttackComponent);
	if (Interface)
	{
		Interface->SetBow(Cast<ABow>(WeaponBase));
	}
}

void ACharacterBase::EquipStaff()
{
	if (WeaponBase)
	{
		WeaponBase->Destroy();
	}

	FVector SpawnLocation = GetMesh()->GetSocketLocation(TEXT("hand_rSocket"));
	FRotator SpawnRotation = GetMesh()->GetSocketRotation(TEXT("hand_rSocket"));

	WeaponBase = GetWorld()->SpawnActor<AStaff>(StaffClass, SpawnLocation, SpawnRotation);
	WeaponBase->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("hand_rSocket"));
}

//구현 보류
void ACharacterBase::StopInput()
{
	GetPlayerController()->DisableInput(GetPlayerController());
}

void ACharacterBase::ToggleParrying()
{
	if (bIsParrying == false) bIsParrying = true;
	else bIsParrying = false;
}

void ACharacterBase::SetupHUDWidget(UHUDWidget* InHUDWidget)
{
	if (InHUDWidget) 
	{
		InHUDWidget->SetMaxHp(Stat->GetMaxHp());
		InHUDWidget->UpdateHpBar(Stat->GetCurrentHp());
		InHUDWidget->UpdateExpBar(Stat->GetCurrentExp());
		Stat->OnHpChanged.AddUObject(InHUDWidget, &UHUDWidget::UpdateHpBar);
		Stat->OnExpChanged.AddUObject(InHUDWidget, &UHUDWidget::UpdateExpBar);
	}

}

ACPlayerController* ACharacterBase::GetPlayerController() const
{
	return Cast<ACPlayerController>(GetController());
}