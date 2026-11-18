#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "KurdishLifeVehiclePawn.generated.h"

UCLASS()
class KURDISHLIFE_API AKurdishLifeVehiclePawn : public APawn
{
    GENERATED_BODY()
public:
    AKurdishLifeVehiclePawn();
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
    virtual void Tick(float DeltaSeconds) override;
protected:
    void Throttle(float V);
    void Steer(float V);
    void BrakePressed();
    void BrakeReleased();
private:
    UPROPERTY(VisibleAnywhere)
    class UStaticMeshComponent* CarBody;
    UPROPERTY(VisibleAnywhere)
    class USpringArmComponent* CameraBoom;
    UPROPERTY(VisibleAnywhere)
    class UCameraComponent* FollowCamera;
    float Speed = 0.0f;
    float Steering = 0.0f;
    float ThrottleInput = 0.0f;
    bool bBraking = false;
};
