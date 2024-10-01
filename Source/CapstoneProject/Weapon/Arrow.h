// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/ProjectileBase.h"
#include "Arrow.generated.h"

UCLASS()
class CAPSTONEPROJECT_API AArrow : public AProjectileBase
{
	GENERATED_BODY()
	
public:	
	AArrow();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	void Init(const FVector& InDirection, const FVector& CurrentLocation, const FRotator& CurrentRotation);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


private:
	UPROPERTY(VisibleAnywhere, Category = "Root")
	TObjectPtr<class USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, Category = "Box")
	TObjectPtr<class UBoxComponent> Box;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	TObjectPtr<class UStaticMeshComponent> Mesh;

	FVector Direction;

	UPROPERTY(EditAnywhere, Category = "Speed")
	float MoveSpeed;

	UPROPERTY(EditAnywhere, Category = "Time")
	float LifeTime;

	UPROPERTY(EditAnywhere, Category = "Damage")
	float Damage;
};
