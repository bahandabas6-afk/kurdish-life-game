#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "KurdishLifeCharacter.generated.h"

UCLASS()
class KURDISHLIFE_API AKurdishLifeCharacter : public ACharacter
{
    GENERATED_BODY()
public:
    AKurdishLifeCharacter();
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
protected:
    void MoveForward(float Value);
    void MoveRight(float Value);
    void Turn(float Value);
    void LookUp(float Value);
    void SprintPressed();
    void SprintReleased();
private:
    UPROPERTY(VisibleAnywhere, Category="Camera")
    class USpringArmComponent* CameraBoom;
    UPROPERTY(VisibleAnywhere, Category="Camera")
    class UCameraComponent* FollowCamera;
    UPROPERTY(EditAnywhere, Category="Movement")
    float WalkSpeed = 500.0f;
    UPROPERTY(EditAnywhere, Category="Movement")
    float SprintSpeed = 850.0f;
};
