#include "TankPawn.h"
#include "TankPlayerController.h"
#include "Components/AudioComponent.h"
#include "Engine/TargetPoint.h"
#include "Kismet/KismetMathLibrary.h"





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

void ATankPawn::RotateTurretTo(FVector TargetPosition)
{
	if (!IsValid(TurretMesh))
	{
		return;
	}

	FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetPosition);
	FRotator turretRotation = TurretMesh->GetComponentRotation();
	FRotator bodyRotation = GetActorRotation();
	float angleTurretYawRad = UKismetMathLibrary::DegreesToRadians(targetRotation.Yaw - bodyRotation.Yaw);
	targetRotation.Pitch = bodyRotation.Pitch * UKismetMathLibrary::Cos(angleTurretYawRad) - bodyRotation.Roll * UKismetMathLibrary::Sin(angleTurretYawRad);
	targetRotation.Roll = bodyRotation.Roll * UKismetMathLibrary::Cos(angleTurretYawRad) + bodyRotation.Pitch * UKismetMathLibrary::Sin(angleTurretYawRad);

	TurretMesh->SetWorldRotation(FMath::Lerp(turretRotation, targetRotation, TurretRotationInterpolationKey));
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
