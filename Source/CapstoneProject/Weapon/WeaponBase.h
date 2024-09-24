// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

UCLASS()
class CAPSTONEPROJECT_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeaponBase();

protected:
	virtual void BeginPlay() override;

public:
	FORCEINLINE USkeletalMeshComponent* GetMesh() { return Mesh; }

protected:
	UPROPERTY(VisibleAnywhere, Category = "Root")
	TObjectPtr<class USceneComponent> Root;


	UPROPERTY(EditAnywhere, Category = "Mesh")
	TObjectPtr<class USkeletalMeshComponent> Mesh;

	
	
};
