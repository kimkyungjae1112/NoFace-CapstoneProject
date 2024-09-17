// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/EnemyDefaultAttackNotify.h"
#include "Interface/AIInterface.h"

UEnemyDefaultAttackNotify::UEnemyDefaultAttackNotify()
{
}

void UEnemyDefaultAttackNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	IAIInterface* Interface = Cast<IAIInterface>(MeshComp->GetOwner());
	if (Interface)
	{
		Interface->DefaultAttackHitCheck();
	}
}
