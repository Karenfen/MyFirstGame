#include "TankPlayerController.h"
#include "DrawDebugHelpers.h"
#include "math.h"
#include "PlayerTankPawn.h"
#include "../HUD/PauseMenuWidget.h"
#include <Kismet/GameplayStatics.h>
#include "../HUD/DeathScreenWidget.h"



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
	InputComponent->BindAction("Pause", IE_Pressed, this, &ATankPlayerController::Pause);
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!GamepadControll && IsValid(TankPawn))
	{
		MousePositionUpdate();
	}
}

FVector ATankPlayerController::GetTurretTarget()
{
	if (GamepadControll && IsValid(TankPawn))
	{
		return (FVector(TurretForwardDirectionValue, TurretRightDirectionValue, 0.0f) + TankPawn->GetActorLocation());
	}

	return MousePosition;
}

FVector ATankPlayerController::GetTankTargetRotation()
{
	if (GamepadControll && IsValid(TankPawn))
	{
		return (FVector(TankForwardDirectionValue, TankRightDirectionValue, 0.0f) + TankPawn->GetActorLocation());
	}

	return FVector::ZeroVector;
}

void ATankPlayerController::Unpause()
{
	SetPause(false);

	if(IsValid(PauseMenu))
	{
		PauseMenu->RemoveFromViewport();
	}
}

void ATankPlayerController::Pause()
{
	if (!IsValid(PauseMenu))
	{
		return;
	}
			
	Super::Pause();

	PauseMenu->AddToViewport();
}

void ATankPlayerController::SetGamePadControll(bool isGamePad)
{
	GamepadControll = isGamePad;

	if (GamepadControll)
	{
		bShowMouseCursor = false;
	}
	else
	{
		bShowMouseCursor = true;
	}
}

void ATankPlayerController::Quit()
{
	UGameplayStatics::OpenLevel(GetWorld(), mainMenuLevelName);
}

void ATankPlayerController::Restart()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(GetWorld()->GetName()));
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;
	SetInputMode(FInputModeGameAndUI());

	TankPawn = Cast<APlayerTankPawn>(GetPawn());
	if (IsValid(TankPawn))
	{
		TankPawn->OnDie.AddUObject(this, &ATankPlayerController::PlayerIsDie);
	}

	PauseMenu = CreateWidget<UPauseMenuWidget>(this, PauseMenuClass);
	if (IsValid(PauseMenu))
	{
		PauseMenu->SetButtonClickeHandler(this);
	}
}

void ATankPlayerController::MoveForward(float AxisValue)
{
	if (!IsValid(TankPawn))
	{
		return;
	}

	if (GamepadControll)
	{
		if (AxisValue != 0.0f)
		{
			TankForwardDirectionValue = AxisValue;
		}

		TankForwardSpeedValue = AxisValue;

		TankPawn->MoveForward(FVector::Distance(FVector::ZeroVector, FVector(TankForwardSpeedValue, TankRightSpeedValue, 0.0f)));
	}
	else
	{
		TankPawn->MoveForward(AxisValue);
	}
}

void ATankPlayerController::MoveRight(float AxisValue)
{
	if(AxisValue != 0.0f)
		TankRightDirectionValue = AxisValue;

	TankRightSpeedValue = AxisValue;
}

void ATankPlayerController::RotateRight(float AxisValue)
{
	if (IsValid(TankPawn))
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

void ATankPlayerController::SetTurretDirForward(float AxisValue)
{
	if(AxisValue != 0.0f)
		TurretForwardDirectionValue = AxisValue;
}

void ATankPlayerController::SetTurretDirRight(float AxisValue)
{
	if (AxisValue != 0.0f)
		TurretRightDirectionValue = AxisValue;
}

void ATankPlayerController::PlayerIsDie()
{
	DeathScreen = CreateWidget<UDeathScreenWidget>(this, DeathScreenClass);
	if (IsValid(DeathScreen))
	{
		DeathScreen->SetButtonClickeHandler(this);
		DeathScreen->AddToViewport();
	}
	
}
