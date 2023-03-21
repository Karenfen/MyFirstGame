#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"


UCLASS()
class MYPROJECT_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	class APlayerTankPawn* TankPawn {nullptr};

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Component")
	class UPauseMenuWidget* PauseMenu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pause Menu")
	TSubclassOf<class UPauseMenuWidget> PauseMenuClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level loading params")
	FName mainMenuLevelName;

public:
	ATankPlayerController();
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaTime) override;
	FVector GetTurretTarget();
	FVector GetTankTargetRotation();
	UFUNCTION()
	void Unpause();
	UFUNCTION()
	void Quit();
	virtual void Pause() override;
	UFUNCTION()
	void SetGamePadControll(bool isGamePad);

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
	float TurretForwardDirectionValue;
	float TurretRightDirectionValue;
	float TankForwardDirectionValue;
	float TankRightDirectionValue;
	float TankForwardSpeedValue;
	float TankRightSpeedValue;
	bool GamepadControll = false;
};
