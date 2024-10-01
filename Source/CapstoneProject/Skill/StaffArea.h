// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/ProjectileBase.h"
#include "StaffArea.generated.h"

UCLASS()
class CAPSTONEPROJECT_API AStaffArea : public AProjectileBase
{
	GENERATED_BODY()
	
public:	
	AStaffArea();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;


private:
	bool CheckInArea();
	void PullToCenter(float DeltaTime);

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	TObjectPtr<class UStaticMeshComponent> Area;

	TArray<FOverlapResult> OverlapResults;

	UPROPERTY(EditAnywhere, Category = "LifeTime")
	float LifeTime;

	float Damage;
	float DamageTime;

};
