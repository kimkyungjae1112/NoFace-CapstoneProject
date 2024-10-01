#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "RoomActor.generated.h"

UCLASS()
class CAPSTONEPROJECT_API ARoomActor : public AActor
{
    GENERATED_BODY()

public:
    ARoomActor();

protected:
    virtual void BeginPlay() override;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room")
    UStaticMeshComponent* MeshComponent;
};
