#include "TankPawn.h"
#include "TankPlayerController.h"
#include "Components/AudioComponent.h"
#include "Engine/TargetPoint.h"
#include "Kismet/KismetMathLibrary.h"





ATankPawn::ATankPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	AudioSetupCannon = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioSetupCannon"));
	AudioSetupCannon->SetupAttachment(TurretMesh);
	AudioSetupCannon->SetAutoActivate(false);

	AudioMoving = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioMoving"));
	AudioMoving->SetupAttachment(BodyMesh);
	AudioMoving->SetAutoActivate(false);

	AudioHalt = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioHalt"));
	AudioHalt->SetupAttachment(BodyMesh);
	AudioHalt->SetAutoActivate(false);

	AudioHit = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioHit"));
	AudioHit->SetupAttachment(BodyMesh);
	AudioHit->SetAutoActivate(false);
}

void ATankPawn::SetupCannon(TSubclassOf<ACannon> newCannonClass)
{
	Super::SetupCannon(newCannonClass);

	if (AudioSetupCannon)
	{
		AudioSetupCannon->Play();
	}
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
	float angleTurretYawRelativeBody = UKismetMathLibrary::DegreesToRadians(targetRotation.Yaw - bodyRotation.Yaw);

	targetRotation.Pitch = bodyRotation.Pitch * UKismetMathLibrary::Cos(angleTurretYawRelativeBody) - bodyRotation.Roll * UKismetMathLibrary::Sin(angleTurretYawRelativeBody);
	targetRotation.Roll = bodyRotation.Roll * UKismetMathLibrary::Cos(angleTurretYawRelativeBody) + bodyRotation.Pitch * UKismetMathLibrary::Sin(angleTurretYawRelativeBody);

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
	{
		if (IsValid(AudioHalt))
		{
			if (!AudioHalt->IsActive())
				AudioHalt->Play();
		}
		if (IsValid(AudioMoving))
		{
			if (AudioMoving->IsActive())
				AudioMoving->Stop();
		}
		return;
	}

	if (IsValid(AudioMoving))
	{
		if(!AudioMoving->IsActive())
			AudioMoving->Play();
	}
	if (IsValid(AudioHalt))
	{
		if (AudioHalt->IsActive())
			AudioHalt->Stop();
	}

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

void ATankPawn::TakeDamage_(FDamageData DamageData)
{
	Super::TakeDamage_(DamageData);

	if (IsValid(AudioHit))
	{
		AudioHit->Play();
	}
}
