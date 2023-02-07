#include "TankPlayerController.h"
#include "TankPawn.h"
#include "DrawDebugHelpers.h"
#include "math.h"

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
	InputComponent->BindAction("FireSpecial", IE_Pressed, this, &ATankPlayerController::FireSpecial);
	InputComponent->BindAction("SwitchCannon", IE_Pressed, this, &ATankPlayerController::SwitchCannon);
	InputComponent->BindAxis("TurretDirX", this, &ATankPlayerController::SetTurretDirForward);
	InputComponent->BindAxis("TurretDirY", this, &ATankPlayerController::SetTurretDirRight);
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
	if(TankPawn)
		TankPawn->MoveForward(AxisValue);
}

void ATankPlayerController::MoveRight(float AxisValue)
{
	if (TankPawn)
		TankPawn->MoveRight(AxisValue);
}

void ATankPlayerController::RotateRight(float AxisValue)
{
	if (TankPawn)
		TankPawn->RotateRight(AxisValue);
}

void ATankPlayerController::MousePositionUpdate()
{
	FVector mouseDirection;
	DeprojectMousePositionToWorld(MousePosition, mouseDirection);
	FVector pawnPos = TankPawn->GetActorLocation();
	MousePosition.Z = pawnPos.Z;
	FVector dir = MousePosition - pawnPos;
	dir.Normalize();
	MousePosition = pawnPos + dir * 1000;
}

void ATankPlayerController::Fire()
{
	if (TankPawn)
		TankPawn->Fire();
}

void ATankPlayerController::FireSpecial()
{
	if (TankPawn)
		TankPawn->FireSpecial();
}

void ATankPlayerController::SwitchCannon()
{
	if (TankPawn)
		TankPawn->SwitchCannon();
}

void ATankPlayerController::TurretRotateRight(float AxisValue)
{
	
}

void ATankPlayerController::SetTurretDirForward(float AxisValue)
{
	if (TankPawn)
		TankPawn->SetTurretDirX(AxisValue);
}

void ATankPlayerController::SetTurretDirRight(float AxisValue)
{
	if (TankPawn)
		TankPawn->SetTurretDirY(AxisValue);
}
