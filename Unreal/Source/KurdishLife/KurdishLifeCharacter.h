#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "KurdishLifeCharacter.generated.h"

class UStaticMeshComponent;

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

    // Simple engine-shape proxy so the character is visible before custom art is added.
    UPROPERTY(VisibleAnywhere, Category="Preview")
    UStaticMeshComponent* PreviewTorso;
    UPROPERTY(VisibleAnywhere, Category="Preview")
    UStaticMeshComponent* PreviewHead;
    UPROPERTY(VisibleAnywhere, Category="Preview")
    UStaticMeshComponent* PreviewLeftArm;
    UPROPERTY(VisibleAnywhere, Category="Preview")
    UStaticMeshComponent* PreviewRightArm;
    UPROPERTY(VisibleAnywhere, Category="Preview")
    UStaticMeshComponent* PreviewLeftLeg;
    UPROPERTY(VisibleAnywhere, Category="Preview")
    UStaticMeshComponent* PreviewRightLeg;
    UPROPERTY(VisibleAnywhere, Category="Preview")
    UStaticMeshComponent* PreviewFeet;

    UPROPERTY(EditAnywhere, Category="Movement")
    float WalkSpeed = 500.0f;
    UPROPERTY(EditAnywhere, Category="Movement")
    float SprintSpeed = 850.0f;
};
