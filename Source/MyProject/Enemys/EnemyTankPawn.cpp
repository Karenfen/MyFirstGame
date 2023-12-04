// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTankPawn.h"
#include <Engine/TargetPoint.h>
#include "../Player/PlayerTankPawn.h"
#include "../Cannons/Cannon.h"



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

	Controller->Destroy();

	Super::Die(killer);
}

void AEnemyTankPawn::Fire()
{
	if (!CannonIsReady)
	{
		return;
	}

	Super::Fire();

	if (IsValid(Cannon))
	{
		if (Cannon->IsEmpty())
		{
			CannonIsReady = false;
			GetWorld()->GetTimerManager().SetTimer(ReloadCannonTimerHandle, this, &AEnemyTankPawn::Reload, TimeToReloadCannon, false);
		}
	}
}

void AEnemyTankPawn::Reload()
{
	Resupply(10);
	CannonIsReady = true;
}
