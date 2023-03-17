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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	float MoveAccurency = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Trajectory")
	bool ShowTrajectory = false;

	UPROPERTY(BlueprintReadWrite, Category = "Movement params")
	TArray<FVector> CurrentTrajectory{};

	UPROPERTY(BlueprintReadWrite, Category = "Movement params")
	int32 TragectoryPointIndex {};

public:
	APhysicsProjectile();
	virtual ~APhysicsProjectile();

	virtual void Start() override;
	void SetDestinationPoint(const FVector& endPos);

protected:
	virtual void Move() override;

private:
	FVector DestinationPosition = FVector::ZeroVector;
};
