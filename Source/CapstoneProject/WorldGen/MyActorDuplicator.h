#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "RoomActor.h"  // ARoomActor 포함
#include "MyActorDuplicator.generated.h"

// 방향 정의
UENUM()
enum class EDirection : uint8 {
    UP = 1,
    RIGHT = 2,
    DOWN = 4,
    LEFT = 8
};

// Room 구조체
USTRUCT()
struct FRoom {
    GENERATED_BODY()

    int32 Identity;
    FVector Location;
    bool bIsEndRoom;

    FRoom() : Identity(0), Location(FVector::ZeroVector), bIsEndRoom(false) {}
};

UCLASS()
class CAPSTONEPROJECT_API AMyActorDuplicator : public AActor
{
    GENERATED_BODY()

public:
    AMyActorDuplicator();

protected:
    virtual void BeginPlay() override;

public:
    // Static Mesh를 디테일 패널에서 설정할 수 있도록 변수 선언
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Duplication")
    UStaticMesh* StaticMeshToDuplicate;  // Static Mesh 설정

    // 복제된 Static Mesh의 위치를 이동시키는 단위 길이
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Duplication")
    FVector OffsetDistance = FVector(200.f, 200.f, 0.f);  // 기본값: 200 유닛 X, Y 이동

    // 방 생성 알고리즘의 최대 깊이
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Duplication")
    int32 MaxDepth = 7;

    // 스폰할 방 액터 클래스
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Duplication")
    TSubclassOf<ARoomActor> RoomActorClass;

private:
    // 방을 저장할 배열
    TArray<FRoom> Rooms;

    // 방을 재귀적으로 생성하는 함수
    void CreateRooms(FRoom& CurrentRoom, int32 Depth, EDirection CurrentDir);

    // 방의 랜덤한 방향을 결정
    EDirection GetRandomDirection(EDirection CurrentDir);
};
