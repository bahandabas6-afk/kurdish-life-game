#include "KurdishLifeCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "UObject/ConstructorHelpers.h"

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

    // Visible low-poly placeholder assembled from Unreal's built-in basic shapes.
    // These components deliberately have no collision; the character capsule handles movement.
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
    auto ConfigurePart = [](UStaticMeshComponent* Part, UStaticMesh* Mesh, const FVector& Scale, const FVector& Location)
    {
        if (Mesh) Part->SetStaticMesh(Mesh);
        Part->SetRelativeScale3D(Scale);
        Part->SetRelativeLocation(Location);
        Part->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        Part->SetGenerateOverlapEvents(false);
    };

    PreviewTorso = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PreviewTorso"));
    PreviewTorso->SetupAttachment(GetCapsuleComponent());
    ConfigurePart(PreviewTorso, CubeMesh.Succeeded() ? CubeMesh.Object : nullptr, FVector(0.22f, 0.15f, 0.34f), FVector(0, 0, -4));

    PreviewHead = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PreviewHead"));
    PreviewHead->SetupAttachment(GetCapsuleComponent());
    ConfigurePart(PreviewHead, SphereMesh.Succeeded() ? SphereMesh.Object : nullptr, FVector(0.17f), FVector(0, 0, 49));

    PreviewLeftArm = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PreviewLeftArm"));
    PreviewLeftArm->SetupAttachment(GetCapsuleComponent());
    ConfigurePart(PreviewLeftArm, CubeMesh.Succeeded() ? CubeMesh.Object : nullptr, FVector(0.07f, 0.07f, 0.28f), FVector(0, -29, -3));

    PreviewRightArm = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PreviewRightArm"));
    PreviewRightArm->SetupAttachment(GetCapsuleComponent());
    ConfigurePart(PreviewRightArm, CubeMesh.Succeeded() ? CubeMesh.Object : nullptr, FVector(0.07f, 0.07f, 0.28f), FVector(0, 29, -3));

    PreviewLeftLeg = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PreviewLeftLeg"));
    PreviewLeftLeg->SetupAttachment(GetCapsuleComponent());
    ConfigurePart(PreviewLeftLeg, CubeMesh.Succeeded() ? CubeMesh.Object : nullptr, FVector(0.095f, 0.095f, 0.28f), FVector(0, -11, -59));

    PreviewRightLeg = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PreviewRightLeg"));
    PreviewRightLeg->SetupAttachment(GetCapsuleComponent());
    ConfigurePart(PreviewRightLeg, CubeMesh.Succeeded() ? CubeMesh.Object : nullptr, FVector(0.095f, 0.095f, 0.28f), FVector(0, 11, -59));

    PreviewFeet = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PreviewFeet"));
    PreviewFeet->SetupAttachment(GetCapsuleComponent());
    ConfigurePart(PreviewFeet, CubeMesh.Succeeded() ? CubeMesh.Object : nullptr, FVector(0.13f, 0.10f, 0.07f), FVector(8, 0, -87));

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
