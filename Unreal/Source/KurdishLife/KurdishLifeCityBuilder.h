#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KurdishLifeCityBuilder.generated.h"

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
    UPROPERTY(EditAnywhere, Category="City")
    float BlockSpacing = 1100.0f;
    UPROPERTY(EditAnywhere, Category="City")
    int32 RandomSeed = 42;
private:
    UPROPERTY()
    TArray<TObjectPtr<class UInstancedStaticMeshComponent>> GeneratedMeshes;
    void ClearGenerated();
    class UInstancedStaticMeshComponent* MakeInstances(const TCHAR* Name, UStaticMesh* Mesh, const FTransform& Relative);
};
