// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/SwordDefaultAttackEndNotify.h"
#include "Interface/BowInterface.h"
#include "Character/CharacterDefaultAttackComponent.h"

USwordDefaultAttackEndNotify::USwordDefaultAttackEndNotify()
{
}

void USwordDefaultAttackEndNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	//Default Attack Component 에 구현된 인터페이스가 BowInterface임,, 
	//인터페이스를 무기 종류 말고 공격 종류에 따라 나눴으면 더 이뻤을거 같은데
	IBowInterface* Interface = Cast<IBowInterface>(MeshComp->GetOwner()->GetComponentByClass<UCharacterDefaultAttackComponent>());
	if (Interface)
	{
		Interface->SwordDefaultAttackEnd();
	}
}
