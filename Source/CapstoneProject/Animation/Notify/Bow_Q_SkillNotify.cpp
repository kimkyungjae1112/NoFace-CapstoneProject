// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/Bow_Q_SkillNotify.h"
#include "Interface/BowSkillInterface.h"
#include "Skill/SkillComponent.h"

UBow_Q_SkillNotify::UBow_Q_SkillNotify()
{
}

void UBow_Q_SkillNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	IBowSkillInterface* Interface = Cast<IBowSkillInterface>(MeshComp->GetOwner()->GetComponentByClass<USkillComponent>());
	if (Interface)
	{
		Interface->Bow_Q_Skill();
	}
}
