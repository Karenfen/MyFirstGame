#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "PhysicsProjectile.generated.h"


class UPhysicsComponent;


UCLASS()
class MYPROJECT_API APhysicsProjectile : public AProjectile
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UPhysicsComponent* PhysicsComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UParticleSystemComponent* TrailEffect;

	// добавляем визуальный эффект взрыва
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Effects")
	class UParticleSystemComponent* ExplodeEffect;

	// добавляем аудио эффект взрыва
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Effects")
	class UAudioComponent* ExplodeAudio;

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Explode")
	float ExplodeRadius = 100.0f;

public:
	APhysicsProjectile();

	virtual void Start() override;

protected:
	virtual void Move() override;

	virtual void OnMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor*
			OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool
			bFromSweep, const FHitResult& SweepResult) override;

	void Explode();

	
};
