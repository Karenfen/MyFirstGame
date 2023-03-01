#include "EnemyTurret.h"
#include "TimerManager.h"
#include "PlayerTankPawn.h"
#include "Cannon.h"
#include <Components/AudioComponent.h>


AEnemyTurret::AEnemyTurret()
{

}

void AEnemyTurret::Fire()
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
			GetWorld()->GetTimerManager().SetTimer(RechargeTimerHandle, this, &AEnemyTurret::RechargeCannon, RechargeSpeed, false);
		}
	}
}

void AEnemyTurret::Die(AActor* killer)
{
	APlayerTankPawn* player = Cast<APlayerTankPawn>(killer);
	if (player)
		player->EnemyDestroyed(this);

	Super::Die(killer);
}

void AEnemyTurret::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	GetWorld()->GetTimerManager().SetTimer(_targetingTimerHandle, this,	&AEnemyTurret::Targeting, TargetingRate, true, TargetingRate);
}

void AEnemyTurret::Targeting()
{
	if (!IsPlayerSeen())
		return;

	if (IsPlayerInRange() && IsValid(PlayerPawn))
		RotateTurretTo(PlayerPawn->GetActorLocation());
	else
		return;

	if (CanFire())
		Fire();
}

bool AEnemyTurret::IsPlayerInRange()
{
	return FVector::Distance(PlayerPawn->GetActorLocation(), GetActorLocation()) <= TargetingRange;
}

bool AEnemyTurret::CanFire()
{
	FVector targetingDir = TurretMesh->GetForwardVector();
	FVector dirToPlayer = PlayerPawn->GetActorLocation() - GetActorLocation();
	dirToPlayer.Normalize();
	float aimAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(targetingDir, dirToPlayer)));
	
	return aimAngle <= Accurency;
}

void AEnemyTurret::RechargeCannon()
{
	Resupply(10);
	CannonIsReady = true;
}

bool AEnemyTurret::IsPlayerSeen()
{
	if (PlayerPawn == nullptr)
		return false;

	FVector playerPos = PlayerPawn->GetActorLocation();
	FVector eyesPos = GetEyesPosition();
	FHitResult hitResult;

	FCollisionQueryParams traceParams = FCollisionQueryParams(FName(TEXT("FireTrace")), true, this);
	traceParams.bTraceComplex = true;
	traceParams.AddIgnoredActor(this);
	traceParams.bReturnPhysicalMaterial = false;

	DrawDebugLine(GetWorld(), eyesPos, playerPos, FColor::Red, false, 0.5f, 0, 5);

	if (GetWorld()->LineTraceSingleByChannel(hitResult, eyesPos, playerPos, ECollisionChannel::ECC_Visibility, traceParams))
	{
		APlayerTankPawn* target = Cast<APlayerTankPawn>(hitResult.GetActor());
		if (target)
			return target == PlayerPawn;
	}

	return false;
}
