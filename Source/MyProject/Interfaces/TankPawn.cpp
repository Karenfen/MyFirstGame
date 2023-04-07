#include "TankPawn.h"
#include "../Player/TankPlayerController.h"
#include "Components/AudioComponent.h"
#include "Engine/TargetPoint.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"





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

	FRArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Forward right force fector"));
	FRArrow->SetupAttachment(BodyMesh);

	RRArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Rear right force fector"));
	RRArrow->SetupAttachment(BodyMesh);

	Bottom = CreateDefaultSubobject<UBoxComponent>(TEXT("Bottom collision"));
	Bottom->SetupAttachment(BodyMesh);
}

void ATankPawn::SetupCannon(TSubclassOf<ACannon> newCannonClass)
{
	Super::SetupCannon(newCannonClass);

	if (AudioSetupCannon)
	{
		AudioSetupCannon->Play();
	}
}

FVector ATankPawn::GetTurretWorldLocation()
{
	if (IsValid(TurretMesh))
	{
		return (TurretMesh->GetComponentLocation());
	}

	return GetActorLocation();
}

void ATankPawn::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(Bottom))
	{
		Bottom->OnComponentBeginOverlap.AddDynamic(this, &ATankPawn::BottomStartOverlap);
		Bottom->OnComponentEndOverlap.AddDynamic(this, &ATankPawn::BottomEndOverlap);
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

	FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetTurretWorldLocation(), TargetPosition);
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

	if (_targetForwardAxisValue < 0.0f)
	{
		_targetForwardAxisValue *= 0.7f;
	}
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
	if (BottomOverlapCount == 0)
	{
		return;
	}

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

	BodyMesh->AddForce(GetActorForwardVector() * EnginePower * _targetForwardAxisValue, NAME_None, true);
}

void ATankPawn::Rotate(float DeltaTime)
{
	BodyMesh->AddForceAtLocation(FRArrow->GetForwardVector() * RotationSpeed * EnginePower * _targetRotateRightdAxisValue, FRArrow->GetComponentLocation(), NAME_None);
	
	if(_targetForwardAxisValue == 0.0f)
	{
		BodyMesh->AddForceAtLocation(RRArrow->GetForwardVector() * RotationSpeed * 1.5f * EnginePower * _targetRotateRightdAxisValue, RRArrow->GetComponentLocation(), NAME_None);
	}
}

void ATankPawn::TakeDamage_(FDamageData DamageData)
{
	Super::TakeDamage_(DamageData);

	if (IsValid(AudioHit))
	{
		AudioHit->Play();
	}
}
