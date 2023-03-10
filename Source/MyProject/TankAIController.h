#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ACannon;
struct FTimerHandle;

UCLASS()
class MYPROJECT_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	class AEnemyTankPawn* TankPawn;

	UPROPERTY()
	class APlayerTankPawn* PlayerPawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Move params|Patrol points" , Meta = (MakeEditWidget = true))
	TArray<FVector> PatrollingPoints;

	int32 CurrentPatrolPointIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Move params|Accurency")
	float MovementAccurency = 50.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
	float TargetingRange = 1000;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
	float TargetingSpeed = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
	float Accurency = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon")
	float TimeToSwitchCannon = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon")
	TSubclassOf<ACannon> CurrentCannonClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon")
	TArray<TSubclassOf<ACannon>> PoolCannonClasses;

	FTimerHandle switchCannonTimerHandle;
	int currentCannonIndex = 0;
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void Move();
	float GetRotationValue();
	void Targeting();
	void RotateToPlayer();
	bool IsPlayerInRange();
	bool CanFire();
	void Fire();
	bool IsPlayerSeen();
	void SwitchCannon();
	void Initialize();
};
