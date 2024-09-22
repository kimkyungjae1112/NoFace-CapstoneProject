// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StaffUpGround.generated.h"

UCLASS()
class CAPSTONEPROJECT_API AStaffUpGround : public AActor
{
	GENERATED_BODY()
	
public:	
	AStaffUpGround();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void ActiveGroundUp();

private:
	bool CheckInArea();

private:
	UPROPERTY(VisibleAnywhere, Category = "Root")
	TObjectPtr<class USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	TObjectPtr<class UStaticMeshComponent> Mesh;

	TArray<FOverlapResult> OverlapResults;

	UPROPERTY(EditAnywhere, Category = "LifeTime")
	float LifeTime;
};
