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
	InputComponent->BindAction("StopAutoShots", IE_Released, this, &ATankPlayerController::StopAutoShots);
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
	FVector mouseDirection;
	DeprojectMousePositionToWorld(MousePosition, mouseDirection);
	FVector pawnPos = TankPawn->GetActorLocation();
	MousePosition.Z = pawnPos.Z;
	FVector dir = MousePosition - pawnPos;
	dir.Normalize();
	MousePosition = pawnPos + dir * 1000;
	DrawDebugLine(GetWorld(), pawnPos, MousePosition, FColor::Green, false, 0.1f, 0, 5);
}

void ATankPlayerController::Fire()
{
	TankPawn->Fire();
}

void ATankPlayerController::FireSpecial()
{
	TankPawn->FireSpecial();
}

void ATankPlayerController::StopAutoShots()
{
	TankPawn->StopAutoShots();
}
