// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/ProjectileBase.h"
#include "StaffMeteor.generated.h"

UCLASS()
class CAPSTONEPROJECT_API AStaffMeteor : public AProjectileBase
{
	GENERATED_BODY()
	
public:	
	AStaffMeteor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void Init(const FVector& InDestination);

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, Category = "Box")
	TObjectPtr<class UBoxComponent> Box;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	TObjectPtr<class UStaticMeshComponent> Meteor;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	TObjectPtr<class UStaticMeshComponent> MeteorSpline;

private:
	UPROPERTY(EditAnywhere, Category = "Speed")
	float MoveSpeed;

	UPROPERTY(EditAnywhere, Category = "Damage")
	float Damage;

	FVector Destination;
	bool bStart;
	

};
