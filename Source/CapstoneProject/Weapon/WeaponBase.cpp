// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponBase.h"

AWeaponBase::AWeaponBase()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

}

void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}


