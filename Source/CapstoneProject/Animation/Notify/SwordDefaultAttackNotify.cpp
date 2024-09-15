// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/SwordDefaultAttackNotify.h"
#include "Interface/SwordDefaultAttackInterface.h"
#include "Character/CharacterHitCheckComponent.h"

USwordDefaultAttackNotify::USwordDefaultAttackNotify()
{
}

void USwordDefaultAttackNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ISwordDefaultAttackInterface* Interface = Cast<ISwordDefaultAttackInterface>(MeshComp->GetOwner()->GetComponentByClass<UCharacterHitCheckComponent>());
	if (Interface)
	{
		Interface->SwordDefaultAttackHitCheck();
	}
}
