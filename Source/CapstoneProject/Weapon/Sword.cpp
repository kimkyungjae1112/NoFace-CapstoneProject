// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Sword.h"
#include "Components/BoxComponent.h"
#include "Engine/DamageEvents.h"

ASword::ASword()
{
	Box->OnComponentHit.AddDynamic(this, &ASword::OnHit);
	Box->SetCollisionProfileName(TEXT("NoCollision"));
	//검의 콜리전에 닿았을 시 대미지를 적용하고 싶은데
	//캐릭터가 검을 들고있을 때 캐릭터 콜리전과 검 콜리전이 겹쳐서 이동에 문제가 생김.
	//일단 NoCollision
}

void ASword::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Display, TEXT("Sword On Hit"));
	
	FDamageEvent DamageEvent;
	OtherActor->TakeDamage(50.f, DamageEvent, GetWorld()->GetFirstPlayerController(), GetWorld()->GetFirstPlayerController()->GetPawn());
}
