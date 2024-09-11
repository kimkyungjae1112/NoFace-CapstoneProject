// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WeaponChoiceUI.h"
#include "Components/Button.h"
#include "Player/CPlayerController.h"
#include "Interface/TakeWeaponInterface.h"

UWeaponChoiceUI::UWeaponChoiceUI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UWeaponChoiceUI::NativeConstruct()
{
	Super::NativeConstruct();

	SwordButtonPtr = Cast<UButton>(GetWidgetFromName(TEXT("SwordButton")));
	if (SwordButtonPtr == nullptr) return;

	BowButtonPtr = Cast<UButton>(GetWidgetFromName(TEXT("BowButton")));
	if (BowButtonPtr == nullptr) return;

	StaffButtonPtr = Cast<UButton>(GetWidgetFromName(TEXT("StaffButton")));
	if (StaffButtonPtr == nullptr) return;

	SwordButtonPtr->OnClicked.AddDynamic(this, &UWeaponChoiceUI::OnClickButtonSword);
	BowButtonPtr->OnClicked.AddDynamic(this, &UWeaponChoiceUI::OnClickButtonBow);
	StaffButtonPtr->OnClicked.AddDynamic(this, &UWeaponChoiceUI::OnClickButtonStaff);

	UE_LOG(LogTemp, Warning, TEXT("NativeConstruct 호출"));
}

void UWeaponChoiceUI::OnClickButtonSword()
{
	UE_LOG(LogTemp, Display, TEXT("ClickButton Sword"));
	ITakeWeaponInterface* Interface = Cast<ITakeWeaponInterface>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (Interface)
	{
	
	}
}

void UWeaponChoiceUI::OnClickButtonBow()
{
	UE_LOG(LogTemp, Display, TEXT("ClickButton Bow"));
	ITakeWeaponInterface* Interface = Cast<ITakeWeaponInterface>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (Interface)
	{

	}
}

void UWeaponChoiceUI::OnClickButtonStaff()
{
	UE_LOG(LogTemp, Display, TEXT("ClickButton Staff"));
	ITakeWeaponInterface* Interface = Cast<ITakeWeaponInterface>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (Interface)
	{
		
	}
}

