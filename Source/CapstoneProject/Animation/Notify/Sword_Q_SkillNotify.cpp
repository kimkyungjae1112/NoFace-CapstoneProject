// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/Sword_Q_SkillNotify.h"
#include "Interface/SwordDefaultAttackInterface.h"
#include "Character/CharacterHitCheckComponent.h"

USword_Q_SkillNotify::USword_Q_SkillNotify()
{
}

void USword_Q_SkillNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ISwordDefaultAttackInterface* Interface = Cast<ISwordDefaultAttackInterface>(MeshComp->GetOwner()->GetComponentByClass<UCharacterHitCheckComponent>());
	if (Interface)
	{
		Interface->Sword_Q_SkillHitCheck();
	}
}
