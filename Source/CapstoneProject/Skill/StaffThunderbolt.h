// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/ProjectileBase.h"
#include "StaffThunderbolt.generated.h"

UCLASS()
class CAPSTONEPROJECT_API AStaffThunderbolt : public AProjectileBase
{
	GENERATED_BODY()
	
public:	
	AStaffThunderbolt();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void ActiveThunderbolt();

private:
	bool CheckInArea();

	TArray<FOverlapResult> OverlapResults;

private:
	UPROPERTY(VisibleAnywhere, Category = "Root")
	TObjectPtr<class USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	TObjectPtr<class UStaticMeshComponent> UpPlane;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	TObjectPtr<class UStaticMeshComponent> DownPlane;

	UPROPERTY(EditAnywhere, Category = "LifeTime")
	float LifeTime;

	float Damage;
};
