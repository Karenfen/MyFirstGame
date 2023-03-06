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
	float step = Bezier::t_end / (distance / DistanceInterval);

	for (float intervalPassed = Bezier::t_star; intervalPassed < Bezier::t_end; intervalPassed += step)
	{
		trajectory.Add(CalculateBezierPoint(intervalPassed, StartPos, UpVector, EndPos));
	}

	trajectory.Add(CalculateBezierPoint(Bezier::t_end, StartPos, UpVector, EndPos));

	return trajectory;
}