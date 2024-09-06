// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterWarrior.h"

ACharacterWarrior::ACharacterWarrior()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MainMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Manny.SKM_Manny'"));
	if (MainMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(MainMeshRef.Object);
	}
}

void ACharacterWarrior::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACharacterWarrior::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACharacterWarrior::Q_Skill()
{
	Super::Q_Skill();

	UE_LOG(LogTemp, Display, TEXT("Warrior Q Skill"));
}

void ACharacterWarrior::W_Skill()
{
	Super::W_Skill();
	
	UE_LOG(LogTemp, Display, TEXT("Warrior W Skill"));
}

void ACharacterWarrior::E_Skill()
{
	Super::E_Skill();

	UE_LOG(LogTemp, Display, TEXT("Warrior E Skill"));
}

void ACharacterWarrior::R_Skill()
{
	Super::R_Skill();

	UE_LOG(LogTemp, Display, TEXT("Warrior R Skill"));
}


