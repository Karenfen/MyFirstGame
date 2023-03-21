#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DamageTaker.h"
#include "MachineryActor.h"
#include "TankPawn.generated.h"


class UAudioComponent;

UCLASS()
class MYPROJECT_API ATankPawn : public AMachineryActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
	float MoveSpeed = 200.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
	float EnginePower = 1000.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
	float RotationSpeed = 100.0f;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Effects")
	UAudioComponent* AudioSetupCannon;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Effects")
	UAudioComponent* AudioMoving;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Effects")
	UAudioComponent* AudioHalt;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Effects")
	UAudioComponent* AudioHit;

	float _targetForwardAxisValue = 0.0f;
	float _targetRightdAxisValue = 0.0f;
	float _targetRotateRightdAxisValue = 0.0f;

public:
	ATankPawn();
	virtual ~ATankPawn() {};
	virtual void SetupCannon(TSubclassOf<ACannon> newCannonClass) override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	virtual void RotateTurretTo(FVector TargetPosition)  override;
	UFUNCTION()
	void MoveForward(float AxisValue);
	UFUNCTION()
	void MoveRight(float AxisValue);
	UFUNCTION()
	void RotateRight(float AxisValue);

protected:
	void Move(float DeltaTime);
	virtual void Rotate(float DeltaTime);
	virtual void TakeDamage_(FDamageData DamageData) override;
};
