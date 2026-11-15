#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KurdishLifeCityBuilder.generated.h"

class UMaterialInterface;

UCLASS()
class KURDISHLIFE_API AKurdishLifeCityBuilder : public AActor
{
    GENERATED_BODY()
public:
    AKurdishLifeCityBuilder();
    virtual void OnConstruction(const FTransform& Transform) override;
protected:
    UPROPERTY(EditAnywhere, Category="City", meta=(ClampMin="1", ClampMax="12"))
    int32 BlocksPerSide = 5;
    UPROPERTY(EditAnywhere, Category="City", meta=(ClampMin="700.0"))
    float BlockSpacing = 1100.0f;
    UPROPERTY(EditAnywhere, Category="City")
    int32 RandomSeed = 42;

    UPROPERTY(EditAnywhere, Category="City|Buildings", meta=(ClampMin="0", ClampMax="20"))
    int32 MinBuildingsPerBlock = 3;
    UPROPERTY(EditAnywhere, Category="City|Buildings", meta=(ClampMin="0", ClampMax="20"))
    int32 MaxBuildingsPerBlock = 6;
    UPROPERTY(EditAnywhere, Category="City|Buildings", meta=(ClampMin="100.0"))
    float MinBuildingHeightCm = 220.0f;
    UPROPERTY(EditAnywhere, Category="City|Buildings", meta=(ClampMin="100.0"))
    float MaxBuildingHeightCm = 1250.0f;

    UPROPERTY(EditAnywhere, Category="City|Visuals")
    bool bGenerateGround = true;
    UPROPERTY(EditAnywhere, Category="City|Visuals")
    bool bGenerateSidewalks = true;
    UPROPERTY(EditAnywhere, Category="City|Visuals")
    bool bGenerateStreetLights = true;

    UPROPERTY(EditAnywhere, Category="City|Materials")
    TObjectPtr<UMaterialInterface> GroundMaterial = nullptr;
    UPROPERTY(EditAnywhere, Category="City|Materials")
    TObjectPtr<UMaterialInterface> RoadMaterial = nullptr;
    UPROPERTY(EditAnywhere, Category="City|Materials")
    TObjectPtr<UMaterialInterface> SidewalkMaterial = nullptr;
    UPROPERTY(EditAnywhere, Category="City|Materials")
    TObjectPtr<UMaterialInterface> BuildingMaterial = nullptr;
    UPROPERTY(EditAnywhere, Category="City|Materials")
    TObjectPtr<UMaterialInterface> StreetLightPoleMaterial = nullptr;
    UPROPERTY(EditAnywhere, Category="City|Materials")
    TObjectPtr<UMaterialInterface> StreetLightHeadMaterial = nullptr;
private:
    UPROPERTY()
    TArray<TObjectPtr<class UInstancedStaticMeshComponent>> GeneratedMeshes;
    void ClearGenerated();
    class UInstancedStaticMeshComponent* MakeInstances(const TCHAR* Name, UStaticMesh* Mesh, const FTransform& Relative);
};
