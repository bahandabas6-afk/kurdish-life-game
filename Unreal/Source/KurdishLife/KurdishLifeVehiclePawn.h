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
    virtual void UnPossessed() override;
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

    // Editable placeholder handling values, in centimetres and seconds.
    UPROPERTY(EditAnywhere, Category="Vehicle|Handling", meta=(ClampMin="0.0"))
    float MaxForwardSpeed = 1600.0f;
    UPROPERTY(EditAnywhere, Category="Vehicle|Handling", meta=(ClampMin="0.0"))
    float MaxReverseSpeed = 500.0f;
    UPROPERTY(EditAnywhere, Category="Vehicle|Handling", meta=(ClampMin="0.0"))
    float ForwardAcceleration = 900.0f;
    UPROPERTY(EditAnywhere, Category="Vehicle|Handling", meta=(ClampMin="0.0"))
    float ReverseAcceleration = 650.0f;
    UPROPERTY(EditAnywhere, Category="Vehicle|Handling", meta=(ClampMin="0.0"))
    float BrakeInterpSpeed = 6.0f;
    UPROPERTY(EditAnywhere, Category="Vehicle|Handling", meta=(ClampMin="0.0"))
    float CoastingInterpSpeed = 0.35f;
    UPROPERTY(EditAnywhere, Category="Vehicle|Handling", meta=(ClampMin="0.0"))
    float MaxSteeringRate = 75.0f;

    float Speed = 0.0f;
    float Steering = 0.0f;
    float ThrottleInput = 0.0f;
    bool bBraking = false;
};
