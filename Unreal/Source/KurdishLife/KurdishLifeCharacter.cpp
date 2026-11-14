#include "KurdishLifeCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"

AKurdishLifeCharacter::AKurdishLifeCharacter()
{
    PrimaryActorTick.bCanEverTick = false;
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 360.0f;
    CameraBoom->bUsePawnControlRotation = true;
    CameraBoom->bEnableCameraLag = true;
    CameraBoom->CameraLagSpeed = 10.0f;

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    bUseControllerRotationYaw = false;
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 600.0f, 0.0f);
    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void AKurdishLifeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveForward", this, &AKurdishLifeCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AKurdishLifeCharacter::MoveRight);
    PlayerInputComponent->BindAxis("Turn", this, &AKurdishLifeCharacter::Turn);
    PlayerInputComponent->BindAxis("LookUp", this, &AKurdishLifeCharacter::LookUp);
    PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AKurdishLifeCharacter::SprintPressed);
    PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AKurdishLifeCharacter::SprintReleased);
}
void AKurdishLifeCharacter::MoveForward(float V)
{
    if (Controller && !FMath::IsNearlyZero(V))
        AddMovementInput(FRotationMatrix(FRotator(0, Controller->GetControlRotation().Yaw, 0)).GetUnitAxis(EAxis::X), V);
}
void AKurdishLifeCharacter::MoveRight(float V)
{
    if (Controller && !FMath::IsNearlyZero(V))
        AddMovementInput(FRotationMatrix(FRotator(0, Controller->GetControlRotation().Yaw, 0)).GetUnitAxis(EAxis::Y), V);
}
void AKurdishLifeCharacter::Turn(float V) { AddControllerYawInput(V); }
void AKurdishLifeCharacter::LookUp(float V) { AddControllerPitchInput(V); }
void AKurdishLifeCharacter::SprintPressed() { GetCharacterMovement()->MaxWalkSpeed = SprintSpeed; }
void AKurdishLifeCharacter::SprintReleased() { GetCharacterMovement()->MaxWalkSpeed = WalkSpeed; }
