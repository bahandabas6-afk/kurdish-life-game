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
void AKurdishLifeVehiclePawn::Throttle(float V){Speed=FMath::Clamp(Speed+V*(bBraking?8.0f:18.0f),-500.0f,1600.0f);}
void AKurdishLifeVehiclePawn::Steer(float V){Steering=V;}
void AKurdishLifeVehiclePawn::BrakePressed(){bBraking=true;}
void AKurdishLifeVehiclePawn::BrakeReleased(){bBraking=false;}
