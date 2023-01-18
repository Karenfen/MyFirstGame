#include "TankPlayerController.h"
#include "TankPawn.h"
#include "DrawDebugHelpers.h"

ATankPlayerController::ATankPlayerController()
{
}

void ATankPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis("MoveForward", this, &ATankPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ATankPlayerController::MoveRight);
	InputComponent->BindAxis("RotateRight", this, &ATankPlayerController::RotateRight);
	InputComponent->BindAction("Fire", IE_Pressed, this, &ATankPlayerController::Fire);
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MousePositionUpdate();
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	bShowMouseCursor = true;

	TankPawn = Cast<ATankPawn>(GetPawn());
}

void ATankPlayerController::MoveForward(float AxisValue)
{
	TankPawn->MoveForward(AxisValue);
}

void ATankPlayerController::MoveRight(float AxisValue)
{
	TankPawn->MoveRight(AxisValue);
}

void ATankPlayerController::RotateRight(float AxisValue)
{
	if (TankPawn)
	{
		TankPawn->RotateRight(AxisValue);
	}
}

void ATankPlayerController::MousePositionUpdate()
{
	FVector MouseDirection;
	DeprojectMousePositionToWorld(MousePosition, MouseDirection);
	FVector PawnPosition = TankPawn->GetActorLocation();
	FVector TurretPosition = TankPawn->GetTurretLocation();
	MousePosition.Z = PawnPosition.Z;
	FVector direction = MousePosition - PawnPosition;
	direction.Normalize();
	MousePosition = PawnPosition + direction * 500;
	DrawDebugLine(GetWorld(), TurretPosition, MousePosition, FColor::Red, false, 0.1f, 0, 5);
}

void ATankPlayerController::Fire()
{
	TankPawn->Fire();
}
