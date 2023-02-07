#include "EnemyTurret.h"
#include "TankPlayerController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Cannon.h"
#include "TimerManager.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "HealthComponent.h"
#include "TankPawn.h"

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

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health	component"));
	HealthComponent->OnDie.AddUObject(this, &AEnemyTurret::Die);
	HealthComponent->OnDamaged.AddUObject(this, &AEnemyTurret::DamageTaked);

}

void AEnemyTurret::Fire()
{
	if (Cannon)
	{
		Cannon->Fire();

		if (Cannon->IsEmpty())
		{
			CannonIsReady = false;
			Cannon->Resupply(10);
			GetWorld()->GetTimerManager().SetTimer(RechargeTimerHandle, this, &AEnemyTurret::RechargeCannon, RechargeSpeed, false);
		}
	}
}

void AEnemyTurret::SetupCannon(TSubclassOf<ACannon> newCannonClass)
{
	FActorSpawnParameters params;
	params.Owner = this;

	Cannon = GetWorld()->SpawnActor<ACannon>(newCannonClass, params);
	Cannon->AttachToComponent(CannonSetupPoint, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void AEnemyTurret::TakeDamage(FDamageData DamageData)
{
	HealthComponent->TakeDamage(DamageData);
}

void AEnemyTurret::Die(AActor* killer)
{
	ATankPawn* player = Cast<ATankPawn>(killer);
	if (player)
		player->EnemyDestroyed(this);

	Destroy();
}

void AEnemyTurret::DamageTaked(float DamageValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Turret %s taked damage:%f Health:%f"), *GetName(), DamageValue, HealthComponent->GetHealth());
}

void AEnemyTurret::BeginPlay()
{
	Super::BeginPlay();

	SetupCannon(CannonClass);

	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

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
	if (!IsPlayerSeen())
		return;

	if (IsPlayerInRange())
		RotateTurret(0.0f);
	else
		return;

	if (CanFire() && CannonIsReady)
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

	if (GetWorld()->LineTraceSingleByChannel(hitResult, eyesPos, playerPos, ECollisionChannel::ECC_Visibility, traceParams))
	{
		AActor* target = hitResult.GetActor();
		if (target)
			return target == PlayerPawn;
	}

	return false;
}

FVector AEnemyTurret::GetEyesPosition()
{
	return CannonSetupPoint->GetComponentLocation();
}

