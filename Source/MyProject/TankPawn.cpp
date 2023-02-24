#include "TankPawn.h"
#include "TankPlayerController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/AudioComponent.h"
#include "Engine/TargetPoint.h"


ATankPawn::ATankPawn()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move(DeltaTime);
	Rotate(DeltaTime);
}

void ATankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATankPawn::MoveForward(float AxisValue)
{
	_targetForwardAxisValue = AxisValue;
}

void ATankPawn::MoveRight(float AxisValue)
{
	_targetRightdAxisValue = AxisValue;
}

void ATankPawn::RotateRight(float AxisValue)
{
	_targetRotateRightdAxisValue = AxisValue;
}

void ATankPawn::Move(float DeltaTime)
{
	if (_targetForwardAxisValue == 0.0f)
		return;

	if (RootComponent->IsSimulatingPhysics())
	{
		UPrimitiveComponent* mesh = Cast<UPrimitiveComponent>(RootComponent);
		if (mesh)
		{
			mesh->AddForce(GetActorForwardVector() * EnginePower * DeltaTime * _targetForwardAxisValue, NAME_None, true);
			return;
		}
	}

	FVector currentLocation = GetActorLocation();
	FVector forwardVector = GetActorForwardVector();
	FVector rightVector = GetActorRightVector();
	FVector movePosition = currentLocation + ((forwardVector * _targetForwardAxisValue + rightVector * _targetRightdAxisValue) * MoveSpeed * DeltaTime);
	AActor::SetActorLocation(movePosition, true);
}

void ATankPawn::Rotate(float DeltaTime)
{
	float yawRotation = RotationSpeed * _targetRotateRightdAxisValue * DeltaTime;
	FRotator currentRotation = GetActorRotation();

	currentRotation.Yaw += yawRotation;
	SetActorRotation(currentRotation);
}
