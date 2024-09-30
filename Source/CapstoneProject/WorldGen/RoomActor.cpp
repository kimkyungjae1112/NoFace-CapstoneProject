#include "RoomActor.h"

ARoomActor::ARoomActor()
{
    PrimaryActorTick.bCanEverTick = false;

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    RootComponent = MeshComponent;
}

void ARoomActor::BeginPlay()
{
    Super::BeginPlay();
}
