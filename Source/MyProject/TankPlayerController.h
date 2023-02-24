#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class APlayerTankPawn;

UCLASS()
class MYPROJECT_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		APlayerTankPawn* TankPawn;

public:
	ATankPlayerController();
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaTime) override;
	FVector GetMousePosition() { return MousePosition; };

protected:
	virtual void BeginPlay() override;
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void RotateRight(float ZxisValue);
	void MousePositionUpdate();
	void Fire();
	void FireSpecial();
	void SwitchCannon();
	void SetTurretDirForward(float AxisValue);
	void SetTurretDirRight(float AxisValue);

	FVector MousePosition;
};
