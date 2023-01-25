#include "EnemyTurret.h"
#include "TankPlayerController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Cannon.h"
#include "TimerManager.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"

AEnemyTurret::AEnemyTurret()
{
	PrimaryActorTick.bCanEverTick = false;

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret body"));
	RootComponent = BodyMesh;

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret turret"));
	TurretMesh->AttachToComponent(BodyMesh, FAttachmentTransformRules::KeepRelativeTransform, "ADD_Parts_Here_Socket");

	CannonSetupPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Cannon setup point"));
	CannonSetupPoint->AttachToComponent(TurretMesh,	FAttachmentTransformRules::KeepRelativeTransform, "Cannon_Setup_Socket");

	HitCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Hit collider"));
	HitCollider->SetupAttachment(BodyMesh);

	UStaticMesh * turretMeshTemp = LoadObject<UStaticMesh>(this, *TurretMeshPath);
	if (turretMeshTemp)
		TurretMesh->SetStaticMesh(turretMeshTemp);

	UStaticMesh* bodyMeshTemp = LoadObject<UStaticMesh>(this, *BodyMeshPath);
	if (bodyMeshTemp)
		BodyMesh->SetStaticMesh(bodyMeshTemp);
}

void AEnemyTurret::Fire()
{
	if (Cannon)
		Cannon->Fire();
}

void AEnemyTurret::SetupCannon(TSubclassOf<ACannon> newCannonClass)
{
	FActorSpawnParameters params;
	params.Owner = this;

	Cannon = GetWorld()->SpawnActor<ACannon>(newCannonClass, params);
	Cannon->AttachToComponent(CannonSetupPoint, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void AEnemyTurret::BeginPlay()
{
	Super::BeginPlay();

	SetupCannon(CannonClass);

	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	FTimerHandle _targetingTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(_targetingTimerHandle, this,	&AEnemyTurret::Targeting, TargetingRate, true, TargetingRate);
}

void AEnemyTurret::Destroyed()
{
	if (Cannon)
		Cannon->Destroy();
}

void AEnemyTurret::RotateTurret(float DeltaTime)
{
	FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), PlayerPawn->GetActorLocation());
	FRotator currRotation = TurretMesh->GetComponentRotation();
	targetRotation.Pitch = currRotation.Pitch;
	targetRotation.Roll = currRotation.Roll;
	TurretMesh->SetWorldRotation(FMath::Lerp(currRotation, targetRotation, TargetingSpeed));
}

void AEnemyTurret::Targeting()
{
	if (IsPlayerInRange())
		RotateTurret(0.0f);
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

