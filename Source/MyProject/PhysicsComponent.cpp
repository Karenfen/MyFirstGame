#include "PhysicsComponent.h"
#include "GameStruct.h"


UPhysicsComponent::UPhysicsComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

}

TArray<FVector> UPhysicsComponent::GenerateTrajectory(FVector StartPos, FVector EndPos)
{
	TArray<FVector> trajectory{};
	float distance = FVector::Distance(StartPos, EndPos);
	float maxHeight = distance / 2.0f;
	FVector UpVector = (StartPos + EndPos) / 2.0f;
	UpVector.Z += maxHeight;
	float step = 1.0f / (distance / DistanceImterval);

	for (float intervalPassed = 0.0f; intervalPassed <= 1.0f; intervalPassed += step)
	{
		trajectory.Add(CalculateBezierPoint(intervalPassed, StartPos, UpVector, EndPos));
	}

	return trajectory;
}