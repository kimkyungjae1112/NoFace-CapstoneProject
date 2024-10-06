// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyBase.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "AI/Controller/AIControllerBase.h"
#include "Components/CapsuleComponent.h"
#include "Stat/EnemyStatComponent.h"
#include "UI/EnemyHpBarWidget.h"
#include "UI/EnemyHpBarWidgetComponent.h"

FOnDead AEnemyBase::OnDead;

AEnemyBase::AEnemyBase()
{
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));
	
	Stat = CreateDefaultSubobject<UEnemyStatComponent>(TEXT("Stat"));

	HpBar = CreateDefaultSubobject<UEnemyHpBarWidgetComponent>(TEXT("Widget"));
	HpBar->SetupAttachment(GetMesh());
	HpBar->SetRelativeLocation(FVector(0.f, 0.f, -50.f));
	static ConstructorHelpers::FClassFinder<UEnemyPtrWidget> HpBarWidgetRef(TEXT("/Game/No-Face/UI/WBP_EenmyHpBar.WBP_EenmyHpBar_C"));
	if (HpBarWidgetRef.Class)
	{
		HpBarClass = HpBarWidgetRef.Class;
		HpBar->SetWidgetClass(HpBarClass);
		HpBar->SetWidgetSpace(EWidgetSpace::Screen);
		HpBar->SetDrawSize(FVector2D(150.f, 15.f));
		HpBar->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
}

float AEnemyBase::GetPatrolRadius()
{
	return 800.0f;
}

float AEnemyBase::GetDetectRadius()
{
	return 400.0f;
}

float AEnemyBase::GetAttackInRange()
{
	return 200.0f;
}

float AEnemyBase::GetTurnSpeed()
{
	return 10.0f;
}

void AEnemyBase::SetEnemyAttackDelegate(const FEnemyAttackFinished& InEnemyAttackFinished)
{
	EnemyAttackFinished = InEnemyAttackFinished;
}

void AEnemyBase::SetEnemySkill1Delegate(const FEnemySkill1Finished& InEnemySkill1Finished)
{
	EnemySkill1Finished = InEnemySkill1Finished;
}

void AEnemyBase::AttackByAI()
{
	UE_LOG(LogTemp, Display, TEXT("몬스터 공격"));

}

void AEnemyBase::DefaultAttackHitCheck()
{
}

void AEnemyBase::Skill1ByAI()
{
}

void AEnemyBase::SetupHpBarWidget(UEnemyHpBarWidget* InHpBarWidget)
{
	UEnemyHpBarWidget* HpBarWidget = InHpBarWidget;
	if (HpBarWidget)
	{
		HpBarWidget->SetMaxHp(Stat->GetCurrentHp());
		HpBarWidget->UpdateHpBar(Stat->GetCurrentHp());
		Stat->OnHpChanged.AddUObject(HpBarWidget, &UEnemyHpBarWidget::UpdateHpBar);
	}
}

float AEnemyBase::TakeExp()
{
	//기본 10 경험치
	return 10.f;
}

void AEnemyBase::Stun()
{
	UE_LOG(LogTemp, Display, TEXT("스턴상태!!!!!!!!!!!"));
}

void AEnemyBase::SetDead()
{
	OnDead.ExecuteIfBound(TakeExp());
}







