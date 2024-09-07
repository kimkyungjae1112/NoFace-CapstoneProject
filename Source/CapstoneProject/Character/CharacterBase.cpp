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
#include "Skill/Skill_Q_ChargeAttack.h"
#include "Skill/Skill_Q_DoubleAttack.h"
#include "Skill/Skill_W_UnConfirmed.h"
#include "Skill/Skill_E_UnConfirmed.h"
#include "Skill/Skill_R_UnConfirmed.h"
#include "Stat/CharacterStatComponent.h"

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


	/* 애니메이션 */
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	/* 스킬 */
	CurrentQSkillType = EQSkillType::Double;
	CurrentWSkillType = EWSkillType::UnConfirmed;
	CurrentESkillType = EESkillType::UnConfirmed;
	CurrentRSkillType = ERSkillType::UnConfirmed;

	/* 스텟 */
	Stat = CreateDefaultSubobject<UCharacterStatComponent>(TEXT("Stat"));

}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}

	/* 스킬 */
	Q_SkillMap.Add(EQSkillType::Double, NewObject<USkill_Q_DoubleAttack>(this));
	Q_SkillMap.Add(EQSkillType::Charge, NewObject<USkill_Q_ChargeAttack>(this));
	W_SkillMap.Add(EWSkillType::UnConfirmed, NewObject<USkill_W_UnConfirmed>(this));
	E_SkillMap.Add(EESkillType::UnConfirmed, NewObject<USkill_E_UnConfirmed>(this));
	R_SkillMap.Add(ERSkillType::UnConfirmed, NewObject<USkill_R_UnConfirmed>(this));

	
}

void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	
	EnhancedInputComponent->BindAction(RightClickAction, ETriggerEvent::Started, this, &ACharacterBase::OnClickStart);
	EnhancedInputComponent->BindAction(RightClickAction, ETriggerEvent::Triggered, this, &ACharacterBase::OnClicking);
	EnhancedInputComponent->BindAction(RightClickAction, ETriggerEvent::Completed, this, &ACharacterBase::OnRelease);
	
	EnhancedInputComponent->BindAction(Q_SkillAction, ETriggerEvent::Started, this, &ACharacterBase::Q_Skill);
	EnhancedInputComponent->BindAction(W_SkillAction, ETriggerEvent::Started, this, &ACharacterBase::W_Skill);
	EnhancedInputComponent->BindAction(E_SkillAction, ETriggerEvent::Started, this, &ACharacterBase::E_Skill);
	EnhancedInputComponent->BindAction(R_SkillAction, ETriggerEvent::Started, this, &ACharacterBase::R_Skill);
	
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
	Q_SkillMap[CurrentQSkillType]->ExecuteSkill();
}

void ACharacterBase::W_Skill()
{
	UE_LOG(LogTemp, Display, TEXT("Base W Skill"));
	W_SkillMap[CurrentWSkillType]->ExecuteSkill();
}

void ACharacterBase::E_Skill()
{
	UE_LOG(LogTemp, Display, TEXT("Base E Skill"));
	E_SkillMap[CurrentESkillType]->ExecuteSkill();
}

void ACharacterBase::R_Skill()
{
	UE_LOG(LogTemp, Display, TEXT("Base R Skill"));
	R_SkillMap[CurrentRSkillType]->ExecuteSkill();
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

ACPlayerController* ACharacterBase::GetPlayerController() const
{
	return Cast<ACPlayerController>(GetController());
}

