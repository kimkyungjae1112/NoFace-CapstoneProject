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

/* 해당 클래스는 웨폰 베이스 클래스로 상속받은 무기들은 */
/* Mesh를 디테일 패널에서 바꾸고 있음 */
protected:
	UPROPERTY(VisibleAnywhere, Category = "Root")
	TObjectPtr<class USceneComponent> Root;


	UPROPERTY(EditAnywhere, Category = "Mesh")
	TObjectPtr<class USkeletalMeshComponent> Mesh;

	
	
};
