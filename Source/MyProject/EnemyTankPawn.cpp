// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTankPawn.h"
#include <Engine/TargetPoint.h>
#include "PlayerTankPawn.h"

AEnemyTankPawn::AEnemyTankPawn()
{

}

TArray<FVector> AEnemyTankPawn::GetPatrollingPoints()
{
	TArray<FVector> points;

	for (ATargetPoint* point : PatrollingPoints)
	{
		points.Add(point->GetActorLocation());
	}

	return points;
}

void AEnemyTankPawn::Die(AActor* killer)
{
	APlayerTankPawn* player = Cast<APlayerTankPawn>(killer);
	if (player == APawn::GetWorld()->GetFirstPlayerController()->GetPawn() && player != nullptr)
		player->EnemyDestroyed(this);

	Super::Die(killer);
}
