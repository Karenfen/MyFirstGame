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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UPauseMenuWidget> PauseMenuClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UDeathScreenWidget> DeathScreenClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UNoticeWidget> NoticeClass;

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
	UFUNCTION()
	void Restart();
	virtual void Pause() override;
	UFUNCTION()
	void SetGamePadControll(bool isGamePad);
	UFUNCTION()
	void SaveGame();

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
	UFUNCTION()
	void PlayerIsDie();

private:
	FVector MousePosition;
	float TurretForwardDirectionValue;
	float TurretRightDirectionValue;
	float TankForwardDirectionValue;
	float TankRightDirectionValue;
	float TankForwardSpeedValue;
	float TankRightSpeedValue;
	bool GamepadControll = false;

	class UPauseMenuWidget* PauseMenu {nullptr};
	class UDeathScreenWidget* DeathScreen {nullptr};
	class UNoticeWidget* Notice{nullptr};
};
