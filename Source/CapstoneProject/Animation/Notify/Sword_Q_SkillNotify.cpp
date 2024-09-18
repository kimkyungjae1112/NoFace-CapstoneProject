// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/Sword_Q_SkillNotify.h"
#include "Interface/SwordInterface.h"
#include "Character/CharacterHitCheckComponent.h"

USword_Q_SkillNotify::USword_Q_SkillNotify()
{
}

void USword_Q_SkillNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	//해당 인터페이스는 Sword 공격 및 스킬에 대해 모든 공격 판정을 관리하는 인터페이스이다.
	ISwordInterface* Interface = Cast<ISwordInterface>(MeshComp->GetOwner()->GetComponentByClass<UCharacterHitCheckComponent>());
	if (Interface)
	{
		Interface->Sword_Q_SkillHitCheck();
	}
}
