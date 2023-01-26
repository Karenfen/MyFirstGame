#pragma once

#include "IMachinery.h"
#include "GameFramework/Pawn.h"
#include "DamageTaker.h"
#include "GameStruct.h"
#include "TankPawn.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UBoxComponent;
class UHealthComponent;
class UArrowComponent;

UCLASS()
class MYPROJECT_API ATankPawn : public APawn, public IIMachinery, public IDamageTaker
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* BodyMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UBoxComponent* HitCollider;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UCameraComponent* Camera;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UArrowComponent* CannonSetupPoint;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
	float MoveSpeed = 200.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
	float RotationSpeed = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Rotation")
	float TurretRotationInterpolationKey = 0.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret|Cannon")
	TSubclassOf<ACannon> CannonClass;

	UPROPERTY()
	class ATankPlayerController* TankController;

	UPROPERTY()
	ACannon* Cannon;

	UPROPERTY()
	ACannon* SecondCannon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Scores")
	int CurrentScores;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Scores")
	int MaxScores = 1000000;

	float _targetForwardAxisValue = 0.0f;
	float _targetRightdAxisValue = 0.0f;
	float _targetRotateRightdAxisValue = 0.0f;

public:
	ATankPawn();

	UFUNCTION()
	void MoveForward(float AxisValue);

	UFUNCTION()
	void MoveRight(float AxisValue);

	UFUNCTION()
	void RotateRight(float AxisValue);

	UFUNCTION()
	virtual void Fire() override;

	UFUNCTION()
	void FireSpecial();

	UFUNCTION()
	void SwitchCannon();

	UFUNCTION()
	virtual void TakeDamage(FDamageData DamageData) override;

	UFUNCTION()
	void EnemyDestroyed(AActor* destroyedObject);

	FVector GetTurretLocation() { return TurretMesh->GetComponentLocation(); };
	virtual void SetupCannon(TSubclassOf<ACannon> newCannonClass) override;

protected:
	UFUNCTION()
	virtual void Die(AActor* killer) override;

	UFUNCTION()
	virtual void DamageTaked(float DamageValue) override;

	virtual void BeginPlay() override;
	void Move(float DeltaTime);
	void Rotate(float DeltaTime);
	virtual void RotateTurret(float DeltaTime) override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Resupply(uint8 numberRounds);
};
