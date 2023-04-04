#include "GameStruct.h"
#include "Cannons/Cannon.h"


FVector CalculateBezierPoint(float t, const FVector& P0, const FVector& P1, const FVector& P2)
{
	float u = 1.0f - t;

	return (P0 * u * u) + (P1 * u * t * 2.0f) + (P2 * t * t);
}

bool FPlayerTankState::IsEmpty() const
{
	return (FirstCannon == nullptr && SecondCannon == nullptr);
}

bool FPlayerTankState::operator==(const FPlayerTankState& other) const
{
	return (FirstCannon == other.FirstCannon &&
		FCAmmo == other.FCAmmo &&
		SecondCannon == other.SecondCannon &&
		SCAmmo == other.SCAmmo &&
		CurrentHealth == other.CurrentHealth &&
		Scores == other.Scores);
}
