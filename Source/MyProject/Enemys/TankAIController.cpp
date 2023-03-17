#include "TankAIController.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"
#include "EnemyTankPawn.h"
#include "../Player/PlayerTankPawn.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	Initialize();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsValid(TankPawn))
		Initialize();

	if (!IsValid(TankPawn))
		return;

	Move();

	if(IsPlayerSeen())
		Targeting();
}

void ATankAIController::Move()
{
	if (!IsValid(TankPawn))
		return;

	TankPawn->MoveForward(1.0f);
	TankPawn->RotateRight(GetRotationValue());
}

float ATankAIController::GetRotationValue()
{
	if (CurrentPatrolPointIndex >= PatrollingPoints.Num())
	{
		return 0.0f;
	}

	FVector currentPoint = PatrollingPoints[CurrentPatrolPointIndex];
	FVector pawnLocation = TankPawn->GetActorLocation();

	if (FVector::Distance(currentPoint, pawnLocation) <= MovementAccurency)
	{
		++CurrentPatrolPointIndex;
		if (CurrentPatrolPointIndex >= PatrollingPoints.Num())
			CurrentPatrolPointIndex = 0;
	}

	FVector moveDirection = currentPoint - pawnLocation;
	moveDirection.Normalize();
	FVector forwardDirection = TankPawn->GetActorForwardVector();
	FVector rightDirection = TankPawn->GetActorRightVector();
	
	float forwardAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(forwardDirection, moveDirection)));
	float rightAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(rightDirection, moveDirection)));
	float rotationValue = 0.0f;

	if (forwardAngle > 2.0f)
		rotationValue = 1.0f;

	if (rightAngle > 90.0f)
		rotationValue = -rotationValue;

	return rotationValue;
}

void ATankAIController::Targeting()
{
	if (!IsPlayerInRange())
	{
		return;
	}

	if (CanFire())
	{
		Fire();
	}
	else
	{
		RotateToPlayer();
	}
}

void ATankAIController::RotateToPlayer()
{
	if (IsValid(TankPawn) && IsValid(PlayerPawn))
		TankPawn->RotateTurretTo(PlayerPawn->GetActorLocation());
}

bool ATankAIController::IsPlayerInRange()
{
	if (IsValid(TankPawn) && IsValid(PlayerPawn))
	{
		return FVector::Distance(TankPawn->GetActorLocation(), PlayerPawn->GetActorLocation()) <= TargetingRange;
	}

	return false;
}

bool ATankAIController::CanFire()
{
	if (!IsValid(TankPawn) || !IsValid(PlayerPawn))
	{
		return false;
	}

	FVector targetingDir = TankPawn->GetTurretForwardVector();
	FVector dirToPlayer = PlayerPawn->GetActorLocation() - TankPawn->GetActorLocation();
	dirToPlayer.Normalize();

	float aimAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(targetingDir, dirToPlayer)));
	
	return aimAngle <= Accurency;
}
void ATankAIController::Fire()
{
	if(TankPawn)
		TankPawn->Fire();
}

bool ATankAIController::IsPlayerSeen()
{
	if (!PlayerPawn)
		Initialize();

	if (PlayerPawn == nullptr || TankPawn == nullptr)
		return false;

	FVector playerPos = PlayerPawn->GetActorLocation();
	FVector eyesPos = TankPawn->GetEyesPosition();
	FHitResult hitResult;

	FCollisionQueryParams traceParams = FCollisionQueryParams(FName(TEXT("FireTrace")), true, this);
	traceParams.bTraceComplex = true;
	traceParams.AddIgnoredActor(TankPawn);
	traceParams.bReturnPhysicalMaterial = false;

	if (GetWorld()->LineTraceSingleByChannel(hitResult, eyesPos, playerPos,	ECollisionChannel::ECC_Visibility, traceParams))
	{
		AActor* target = hitResult.GetActor();
		if (target)
			return target == PlayerPawn;
	}

	return false;
}

void ATankAIController::SwitchCannon()
{
	if (PoolCannonClasses.Num() <= 1 || !TankPawn)
	{
		GetWorld()->GetTimerManager().ClearTimer(switchCannonTimerHandle);
		return;
	}

	++currentCannonIndex;
	if (PoolCannonClasses.Num() <= currentCannonIndex)
		currentCannonIndex = 0;

	CurrentCannonClass = PoolCannonClasses[currentCannonIndex];
	TankPawn->SetupCannon(CurrentCannonClass);
}

void ATankAIController::Initialize()
{
	TankPawn = Cast<AEnemyTankPawn>(GetPawn());
	PlayerPawn = Cast<APlayerTankPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (!TankPawn)
		return;

	FVector pawnLocation = TankPawn->GetActorLocation();
	MovementAccurency = TankPawn->GetMovementAccurency();
	TArray<FVector> points = TankPawn->GetPatrollingPoints();

	for (const FVector& point : points)
	{
		PatrollingPoints.Add(point);
	}

	CurrentPatrolPointIndex = 0;

	CurrentCannonClass = TankPawn->CurentCannonClass();

	if (PoolCannonClasses.Num() == 0)
		PoolCannonClasses.Add(CurrentCannonClass);
	else if (PoolCannonClasses.Num() > 1)
		GetWorld()->GetTimerManager().SetTimer(switchCannonTimerHandle, this, &ATankAIController::SwitchCannon, TimeToSwitchCannon, true, TimeToSwitchCannon);
}