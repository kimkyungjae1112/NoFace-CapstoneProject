// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/Sword_W_SkillNotify.h"
#include "Interface/SwordInterface.h"
#include "Character/CharacterHitCheckComponent.h"

USword_W_SkillNotify::USword_W_SkillNotify()
{
}

void USword_W_SkillNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ISwordInterface* Interface = Cast<ISwordInterface>(MeshComp->GetOwner()->GetComponentByClass<UCharacterHitCheckComponent>());
	if (Interface) 
	{
		Interface->Sword_W_SkillHitCheck();
	}
}