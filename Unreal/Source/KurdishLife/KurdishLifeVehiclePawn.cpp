#include "KurdishLifeVehiclePawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

AKurdishLifeVehiclePawn::AKurdishLifeVehiclePawn()
{
    PrimaryActorTick.bCanEverTick = true;
    CarBody=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CarBody"));
    SetRootComponent(CarBody);
    static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if(Mesh.Succeeded()) CarBody->SetStaticMesh(Mesh.Object);
    CarBody->SetRelativeScale3D(FVector(2.1f,1.0f,0.55f));
    CarBody->SetSimulatePhysics(false);
    CameraBoom=CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength=650.0f;
    CameraBoom->SetRelativeLocation(FVector(0,0,150));
    CameraBoom->bUsePawnControlRotation=true;
    FollowCamera=CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom,USpringArmComponent::SocketName);
    AutoPossessPlayer=EAutoReceiveInput::Disabled;
}
void AKurdishLifeVehiclePawn::SetupPlayerInputComponent(UInputComponent* Input)
{
    Super::SetupPlayerInputComponent(Input);
    Input->BindAxis("VehicleThrottle",this,&AKurdishLifeVehiclePawn::Throttle);
    Input->BindAxis("VehicleSteer",this,&AKurdishLifeVehiclePawn::Steer);
    Input->BindAction("VehicleBrake",IE_Pressed,this,&AKurdishLifeVehiclePawn::BrakePressed);
    Input->BindAction("VehicleBrake",IE_Released,this,&AKurdishLifeVehiclePawn::BrakeReleased);
}
void AKurdishLifeVehiclePawn::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    // Apply acceleration in units per second so handling is less dependent on frame rate.
    if (bBraking)
    {
        Speed = FMath::FInterpTo(Speed, 0.0f, DeltaSeconds, 6.0f);
    }
    else if (!FMath::IsNearlyZero(ThrottleInput))
    {
        const float Acceleration = ThrottleInput > 0.0f ? 900.0f : 650.0f;
        Speed += ThrottleInput * Acceleration * DeltaSeconds;
    }
    else
    {
        Speed = FMath::FInterpTo(Speed, 0.0f, DeltaSeconds, 0.35f);
    }

    Speed = FMath::Clamp(Speed, -500.0f, 1600.0f);

    const float SpeedRatio = FMath::Clamp(FMath::Abs(Speed) / 500.0f, 0.0f, 1.0f);
    const float TravelDirection = FMath::Sign(Speed);
    AddActorLocalRotation(FRotator(0.0f, Steering * TravelDirection * SpeedRatio * 75.0f * DeltaSeconds, 0.0f));
    AddActorLocalOffset(FVector(Speed * DeltaSeconds, 0.0f, 0.0f), true);
}
void AKurdishLifeVehiclePawn::Throttle(float V)
{
    ThrottleInput = FMath::Clamp(V, -1.0f, 1.0f);
}
void AKurdishLifeVehiclePawn::Steer(float V)
{
    Steering = FMath::Clamp(V, -1.0f, 1.0f);
}
void AKurdishLifeVehiclePawn::BrakePressed(){bBraking=true;}
void AKurdishLifeVehiclePawn::BrakeReleased(){bBraking=false;}

void AKurdishLifeVehiclePawn::UnPossessed()
{
    Super::UnPossessed();

    // Do not let stale input keep moving the placeholder vehicle after control is removed.
    ThrottleInput = 0.0f;
    Steering = 0.0f;
    bBraking = false;
    Speed = 0.0f;
}
