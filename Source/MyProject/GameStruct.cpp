#include "GameStruct.h"

FVector CalculateBezierPoint(float t, const FVector& P0, const FVector& P1, const FVector& P2)
{
	float u = 1.0f - t;

	return (P0 * u * u) + (P1 * u * t * 2.0f) + (P2 * t * t);
}
