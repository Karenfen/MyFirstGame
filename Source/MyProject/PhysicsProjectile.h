#pragma once

#include "CoreMinimal.h"
#include "ProjectileForPool.h"
#include "PhysicsProjectile.generated.h"


class UPhysicsComponent;


UCLASS()
class MYPROJECT_API APhysicsProjectile : public AProjectileForPool
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UPhysicsComponent* PhysicsComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UParticleSystemComponent* TrailEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	float MoveAccurency = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Trajectory")
	float TrajectorySimulationMaxTime = 50.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Trajectory")
	float TrajectorySimulationTimeStep = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Trajectory")
	float TrajectorySimulationSpeed = 20.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Trajectory")
	bool ShowTrajectory = false;

	UPROPERTY(BlueprintReadWrite, Category = "Movement params")
	FVector MoveVector;

	UPROPERTY(BlueprintReadWrite, Category = "Movement params")
	TArray<FVector> CurrentTrajectory;

	UPROPERTY(BlueprintReadWrite, Category = "Movement params")
	int32 TragectoryPointIndex;

public:
	APhysicsProjectile();
	virtual ~APhysicsProjectile();

	virtual void Start() override;

protected:
	virtual void Move() override;

};
