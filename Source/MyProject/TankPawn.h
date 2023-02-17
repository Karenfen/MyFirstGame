#pragma once

#include "IMachinery.h"
#include "GameFramework/Pawn.h"
#include "DamageTaker.h"
#include "GameStruct.h"
#include "IScorable.h"
#include "TankPawn.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UBoxComponent;
class UHealthComponent;
class UArrowComponent;
class UAudioComponent;
class ATargetPoint;

UCLASS()
class MYPROJECT_API ATankPawn : public APawn, public IIMachinery, public IDamageTaker, public IIScorable
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* BodyMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UCameraComponent* Camera;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UArrowComponent* CannonSetupPoint;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UHealthComponent* HealthComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Effects")
	UAudioComponent* AudioChangeCannon;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Effects")
	UAudioComponent* AudioSetupCannon;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Effects")
	UAudioComponent* AudioResupply;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
	float MoveSpeed = 200.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
	float EnginePower = 1000.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
	float RotationSpeed = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Rotation")
	float TurretRotationInterpolationKey = 0.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret|Cannon")
	TSubclassOf<ACannon> CannonClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Move params|Patrol points" , Meta = (MakeEditWidget = true))
	TArray<ATargetPoint*> PatrollingPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Move	params | Accurency")
	float MovementAccurency = 50;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scores")
	float Scores = 100.0f;

	float _targetForwardAxisValue = 0.0f;
	float _targetRightdAxisValue = 0.0f;
	float _targetRotateRightdAxisValue = 0.0f;
	float _TurretDirX = 0.0f;
	float _TurretDirY = 0.0f;

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

	UFUNCTION()
	float GetMovementAccurency() { return MovementAccurency; };

	virtual void SetupCannon(TSubclassOf<ACannon> newCannonClass) override;

	UFUNCTION()
	FVector GetTurretForwardVector();

	UFUNCTION()
	void RotateTurretTo(FVector TargetPosition);

	UFUNCTION()
		void SetTurretDirX(float AxisValue);

	UFUNCTION()
		void SetTurretDirY(float AxisValue);

	UFUNCTION()
	virtual float GetScores() override { return Scores; };
	
	UFUNCTION()
		TSubclassOf<ACannon> CurentCannonClass();

protected:
	UFUNCTION()
	virtual void Die(AActor* killer) override;

	UFUNCTION()
	virtual void DamageTaked(float DamageValue) override;

	virtual void BeginPlay() override;
	void Move(float DeltaTime);
	void Rotate(float DeltaTime);
	virtual void RotateTurret(float DeltaTime) override;
	virtual void Destroyed() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Resupply(uint8 numberRounds);
	FVector GetEyesPosition();
	TArray<FVector> GetPatrollingPoints();
	void  SetPatrollingPoints(TArray<ATargetPoint*> NewPatrollingPoints);
};
