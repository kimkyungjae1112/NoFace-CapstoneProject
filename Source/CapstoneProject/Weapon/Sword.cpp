// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Sword.h"
#include "Components/BoxComponent.h"

ASword::ASword()
{
	Box->OnComponentHit.AddDynamic(this, &ASword::OnHit);

}

void ASword::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Display, TEXT("Sword On Hit"));
}
