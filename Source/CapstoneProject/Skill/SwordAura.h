// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/ProjectileBase.h"
#include "SwordAura.generated.h"

UCLASS()
class CAPSTONEPROJECT_API ASwordAura : public AProjectileBase
{
	GENERATED_BODY()
	
public:	
	ASwordAura();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void Init(const FVector& InMoveDirection);

private:
	UPROPERTY(VisibleAnywhere, Category = "Box")
	TObjectPtr<class UBoxComponent> Box;

	FColor Color;
	FVector MoveDirection;

	UPROPERTY(EditAnywhere, Category = "Var")
	float Damage;

	UPROPERTY(EditAnywhere, Category = "Var")
	float MoveSpeed;

	UPROPERTY(EditAnywhere, Category = "Var")
	float LifeTime;
};
