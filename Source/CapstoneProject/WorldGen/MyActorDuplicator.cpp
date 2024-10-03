#include "MyActorDuplicator.h"
#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"  // FMath 사용을 위해 필요

AMyActorDuplicator::AMyActorDuplicator()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AMyActorDuplicator::BeginPlay()
{
    Super::BeginPlay();

    if (StaticMeshToDuplicate && RoomActorClass)
    {
        // 시작 방 설정 (월드 중심)
        FRoom StartRoom;
        StartRoom.Location = GetActorLocation();
        Rooms.Add(StartRoom);

        // 방 생성 시작 (4 방향)
        CreateRooms(StartRoom, MaxDepth, EDirection::UP);
        CreateRooms(StartRoom, MaxDepth, EDirection::DOWN);
        CreateRooms(StartRoom, MaxDepth, EDirection::RIGHT);
        CreateRooms(StartRoom, MaxDepth, EDirection::LEFT);
    }
}

EDirection AMyActorDuplicator::GetRandomDirection(EDirection CurrentDir)
{
    float RandValue = FMath::FRand();
    if (RandValue < 0.5f) {
        return CurrentDir;
    }
    else if (RandValue < 0.75f) {
        return static_cast<EDirection>((static_cast<uint8>(CurrentDir) * 2) % 15);
    }
    else {
        return static_cast<EDirection>((static_cast<uint8>(CurrentDir) * 8) % 15);
    }
}

void AMyActorDuplicator::CreateRooms(FRoom& CurrentRoom, int32 Depth, EDirection CurrentDir)
{
    if (Depth == 0)
    {
        CurrentRoom.bIsEndRoom = true;
        return;
    }

    // 새로운 방향 결정
    EDirection NewDir = GetRandomDirection(CurrentDir);

    // 새로운 방 생성 및 위치 계산
    FRoom NextRoom;
    if (CurrentDir == EDirection::UP)
    {
        NextRoom.Location = CurrentRoom.Location + FVector(0.f, -OffsetDistance.Y, 0.f);
    }
    else if (CurrentDir == EDirection::DOWN)
    {
        NextRoom.Location = CurrentRoom.Location + FVector(0.f, OffsetDistance.Y, 0.f);
    }
    else if (CurrentDir == EDirection::RIGHT)
    {
        NextRoom.Location = CurrentRoom.Location + FVector(OffsetDistance.X, 0.f, 0.f);
    }
    else if (CurrentDir == EDirection::LEFT)
    {
        NextRoom.Location = CurrentRoom.Location + FVector(-OffsetDistance.X, 0.f, 0.f);
    }

    // 중복 방 체크 (이미 생성된 위치인지 확인)
    for (const FRoom& Room : Rooms)
    {
        if (Room.Location.Equals(NextRoom.Location))
        {
            return;
        }
    }

    // 방을 배열에 추가
    Rooms.Add(NextRoom);

    // 새로운 Room 액터 생성
    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    ARoomActor* DuplicatedRoom = GetWorld()->SpawnActor<ARoomActor>(RoomActorClass, NextRoom.Location, FRotator::ZeroRotator, SpawnParams);
    if (DuplicatedRoom)
    {
        DuplicatedRoom->MeshComponent->SetStaticMesh(StaticMeshToDuplicate);
    }

    // 재귀적으로 다음 방 생성
    CreateRooms(NextRoom, Depth - 1, NewDir);
}
