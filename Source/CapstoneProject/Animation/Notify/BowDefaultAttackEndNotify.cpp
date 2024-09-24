// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/BowDefaultAttackEndNotify.h"
#include "Interface/BowInterface.h"
#include "Character/CharacterDefaultAttackComponent.h"

UBowDefaultAttackEndNotify::UBowDefaultAttackEndNotify()
{
}

void UBowDefaultAttackEndNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	IBowInterface* Interface = Cast<IBowInterface>(MeshComp->GetOwner()->GetComponentByClass<UCharacterDefaultAttackComponent>());
	if (Interface)
	{
		Interface->EndAnimation();
	}
}
