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
    for (auto& Component : GeneratedMeshes)
    {
        if (Component) Component->DestroyComponent();
    }
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
    UStaticMesh* Cylinder = LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
    if (!Cube) return;

    auto* Roads = MakeInstances(TEXT("RoadInstances"), Cube, FTransform::Identity);
    auto* Sidewalks = bGenerateSidewalks ? MakeInstances(TEXT("SidewalkInstances"), Cube, FTransform::Identity) : nullptr;
    auto* Buildings = MakeInstances(TEXT("BuildingInstances"), Cube, FTransform::Identity);
    auto* Ground = bGenerateGround ? MakeInstances(TEXT("GroundInstances"), Cube, FTransform::Identity) : nullptr;
    auto* StreetLightPoles = (bGenerateStreetLights && Cylinder) ? MakeInstances(TEXT("StreetLightPoles"), Cylinder, FTransform::Identity) : nullptr;
    auto* StreetLightHeads = (bGenerateStreetLights && Cylinder) ? MakeInstances(TEXT("StreetLightHeads"), Cylinder, FTransform::Identity) : nullptr;

    if (GroundMaterial && Ground) Ground->SetMaterial(0, GroundMaterial);
    if (RoadMaterial) Roads->SetMaterial(0, RoadMaterial);
    if (SidewalkMaterial && Sidewalks) Sidewalks->SetMaterial(0, SidewalkMaterial);
    if (BuildingMaterial) Buildings->SetMaterial(0, BuildingMaterial);
    if (StreetLightPoleMaterial && StreetLightPoles) StreetLightPoles->SetMaterial(0, StreetLightPoleMaterial);
    if (StreetLightHeadMaterial && StreetLightHeads) StreetLightHeads->SetMaterial(0, StreetLightHeadMaterial);

    const float Half = BlocksPerSide * BlockSpacing * 0.5f;
    const float CityScale = Half / 50.0f; // Cube mesh is 100 cm wide.
    if (Ground)
        Ground->AddInstance(FTransform(FRotator::ZeroRotator, FVector(0,0,-65), FVector(CityScale,CityScale,0.1f)));

    // Broad road strips at each grid line; the perpendicular axis spans the whole district.
    for (int32 I=0; I<=BlocksPerSide; ++I)
    {
        const float P = -Half + I*BlockSpacing;
        Roads->AddInstance(FTransform(FRotator::ZeroRotator,FVector(P,0,-8),FVector(3.0f,CityScale,0.08f)));
        Roads->AddInstance(FTransform(FRotator::ZeroRotator,FVector(0,P,-8),FVector(CityScale,3.0f,0.08f)));

        // Raised sidewalks alongside each road.
        if (Sidewalks)
        {
            for (float Side : {-1.0f, 1.0f})
            {
                Sidewalks->AddInstance(FTransform(FRotator::ZeroRotator,FVector(P+Side*380.0f,0,8),FVector(1.0f,CityScale,0.12f)));
                Sidewalks->AddInstance(FTransform(FRotator::ZeroRotator,FVector(0,P+Side*380.0f,8),FVector(CityScale,1.0f,0.12f)));
            }
        }

        // Repeated street lights make the greybox streets easier to read at scale.
        if (StreetLightPoles && StreetLightHeads)
        {
            for (int32 L=0; L<BlocksPerSide; ++L)
            {
                const float Along = -Half + (L+0.5f)*BlockSpacing;
                for (float Side : {-1.0f, 1.0f})
                {
                    const FVector A(P+Side*470.0f, Along, 0);
                    const FVector B(Along, P+Side*470.0f, 0);
                    for (const FVector& Base : {A,B})
                    {
                        StreetLightPoles->AddInstance(FTransform(FRotator::ZeroRotator,Base+FVector(0,0,230),FVector(0.10f,0.10f,2.3f)));
                        StreetLightHeads->AddInstance(FTransform(FRotator(0,0,90),Base+FVector(0,0,465),FVector(0.24f,0.12f,0.12f)));
                    }
                }
            }
        }
    }

    FRandomStream R(RandomSeed);
    const int32 MinCount = FMath::Clamp(FMath::Min(MinBuildingsPerBlock, MaxBuildingsPerBlock), 0, 20);
    const int32 MaxCount = FMath::Clamp(FMath::Max(MinBuildingsPerBlock, MaxBuildingsPerBlock), MinCount, 20);
    const float MinHeight = FMath::Max(100.0f, FMath::Min(MinBuildingHeightCm, MaxBuildingHeightCm));
    const float MaxHeight = FMath::Max(MinHeight, FMath::Max(MinBuildingHeightCm, MaxBuildingHeightCm));

    for (int32 X=0; X<BlocksPerSide; ++X)
    for (int32 Y=0; Y<BlocksPerSide; ++Y)
    {
        const FVector Center(-Half+(X+0.5f)*BlockSpacing,-Half+(Y+0.5f)*BlockSpacing,0);
        const int32 Count=R.RandRange(MinCount,MaxCount);
        for(int32 B=0; B<Count; ++B)
        {
            const float W=R.FRandRange(180,340);
            const float D=R.FRandRange(180,340);
            const float H=R.FRandRange(MinHeight,MaxHeight);
            const FVector Offset(R.FRandRange(-300,300),R.FRandRange(-300,300),H*0.5f);
            Buildings->AddInstance(FTransform(FRotator(0,R.FRandRange(-4,4),0),Center+Offset,FVector(W/100.0f,D/100.0f,H/100.0f)));
        }
    }
}
