#include "KurdishLifeCityBuilder.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

AKurdishLifeCityBuilder::AKurdishLifeCityBuilder()
{
    PrimaryActorTick.bCanEverTick = false;
    SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Root")));
}
void AKurdishLifeCityBuilder::ClearGenerated()
{
    for (auto* C : GeneratedMeshes) if (C) C->DestroyComponent();
    GeneratedMeshes.Reset();
}
UInstancedStaticMeshComponent* AKurdishLifeCityBuilder::MakeInstances(const TCHAR* Name, UStaticMesh* Mesh, const FTransform& Relative)
{
    auto* C = NewObject<UInstancedStaticMeshComponent>(this, FName(Name));
    C->SetupAttachment(RootComponent);
    C->SetStaticMesh(Mesh);
    C->SetRelativeTransform(Relative);
    C->SetMobility(EComponentMobility::Static);
    C->RegisterComponent();
    GeneratedMeshes.Add(C);
    return C;
}
void AKurdishLifeCityBuilder::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);
    ClearGenerated();
    UStaticMesh* Cube = LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (!Cube) return;
    auto* Roads = MakeInstances(TEXT("RoadInstances"), Cube, FTransform::Identity);
    auto* Buildings = MakeInstances(TEXT("BuildingInstances"), Cube, FTransform::Identity);
    auto* Ground = MakeInstances(TEXT("GroundInstances"), Cube, FTransform::Identity);
    const float Half = BlocksPerSide * BlockSpacing * 0.5f;
    Ground->AddInstance(FTransform(FRotator::ZeroRotator, FVector(0,0,-65), FVector(Half/1000.0f,Half/1000.0f,0.1f)));
    for (int32 I=0; I<=BlocksPerSide; ++I)
    {
        const float P = -Half + I*BlockSpacing;
        Roads->AddInstance(FTransform(FRotator::ZeroRotator,FVector(P,0,0),FVector(0.12f,Half/1000.0f,0.04f)));
        Roads->AddInstance(FTransform(FRotator::ZeroRotator,FVector(0,P,0),FVector(Half/1000.0f,0.12f,0.04f)));
    }
    FRandomStream R(RandomSeed);
    for (int32 X=0; X<BlocksPerSide; ++X)
    for (int32 Y=0; Y<BlocksPerSide; ++Y)
    {
        const FVector Center(-Half+(X+0.5f)*BlockSpacing,-Half+(Y+0.5f)*BlockSpacing,0);
        const int32 Count=R.RandRange(2,5);
        for(int32 B=0; B<Count; ++B)
        {
            const float W=R.FRandRange(130,260);
            const float D=R.FRandRange(130,260);
            const float H=R.FRandRange(180,900);
            const FVector Offset(R.FRandRange(-300,300),R.FRandRange(-300,300),H*0.5f);
            Buildings->AddInstance(FTransform(FRotator(0,R.FRandRange(-4,4),0),Center+Offset,FVector(W/100.0f,D/100.0f,H/100.0f)));
        }
    }
}
