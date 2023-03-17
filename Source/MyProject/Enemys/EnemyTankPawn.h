// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Interfaces/TankPawn.h"
#include "../Interfaces/IScorable.h"
#include "EnemyTankPawn.generated.h"

class ATargetPoint;


UCLASS()
class MYPROJECT_API AEnemyTankPawn : public ATankPawn, public IIScorable
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Move params|Patrol points" , Meta = (MakeEditWidget = true))
	TArray<ATargetPoint*> PatrollingPoints;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Move	params | Accurency")
	float MovementAccurency = 50;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scores")
	int Scores = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon")
	float TimeToReloadCannon = 5.0f;

	FTimerHandle ReloadCannonTimerHandle;
	bool CannonIsReady = true;

public:
	AEnemyTankPawn();
	virtual ~AEnemyTankPawn() {};
	virtual void Fire() override;
	FORCEINLINE virtual int GetScores() override { return Scores; };
	TArray<FVector> GetPatrollingPoints();
	FORCEINLINE void  SetPatrollingPoints(TArray<ATargetPoint*> NewPatrollingPoints) { PatrollingPoints = NewPatrollingPoints; };
	FORCEINLINE float GetMovementAccurency() { return MovementAccurency; };

protected:
	virtual void Die(AActor* killer) override;
	void Reload();
};
