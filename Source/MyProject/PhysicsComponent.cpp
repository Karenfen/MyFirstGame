#include "PhysicsComponent.h"


UPhysicsComponent::UPhysicsComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

}

TArray<FVector> UPhysicsComponent::GenerateTrajectory(FVector StartPos, FVector	Velocity, float MaxTime, float TimeStep, float MinZValue)
{
	TArray<FVector> trajectory;
	FVector gravityVector(0.0f, 0.0f, Gravity);

	for (float time = 0.0f; time < MaxTime; time = time + TimeStep)
	{
		FVector position = StartPos + Velocity * time + gravityVector * time * time / 2;

		if (position.Z <= MinZValue)
			break;

		trajectory.Add(position);
	}

	return trajectory;
}