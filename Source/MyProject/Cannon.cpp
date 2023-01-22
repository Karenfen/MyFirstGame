#include "Cannon.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "Engine/Engine.h"
#include "Engine/EngineTypes.h"
#include "CollisionQueryParams.h"

ACannon::ACannon()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* sceeneCpm = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = sceeneCpm;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cannon mesh"));
	Mesh->SetupAttachment(RootComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawnpoint"));
	ProjectileSpawnPoint->SetupAttachment(Mesh);
}

void ACannon::Fire()
{
	if (!ReadyToFire)
	{
		return;
	}

	if (Ammo <= 0)
	{
		GEngine->AddOnScreenDebugMessage(10, 1, FColor::Red, "Ammo is empty");
		return;
	}

	ReadyToFire = false;

	switch (Type)
	{
	case ECannonType::FireProjectile:
		GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, "Fire - projectile");
		if (ProjectileShot())
			--Ammo;
		break;
	case ECannonType::FireTrace:
		if (TraceShot())
			--Ammo;
		break;
	case ECannonType::FireBurst:
		GetWorld()->GetTimerManager().SetTimer(BurstTimerHandle, this, &ACannon::Burst, 1.0f / BurstRate, true);
		GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, "Fire - burst");
		break;
	}
		
	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this,	&ACannon::Reload, 1.0f / FireRate, false);
}

void ACannon::FireSpecial()
{
	if (!ReadyToFireSpec)
	{
		return;
	}

	if (Ammo <= 0)
	{
		GEngine->AddOnScreenDebugMessage(10, 1, FColor::Red, "Ammo is empty");
		return;
	}

	ReadyToFireSpec = false;

	switch (Type)
	{
	case ECannonType::FireProjectile:
		currentShotInBurst = 2;
		GetWorld()->GetTimerManager().SetTimer(BurstTimerHandle, this, &ACannon::Burst, (1.0f / BurstRate ) * 2.0f, true);
		break;
	case ECannonType::FireTrace:
		if (TraceShot())
			--Ammo;
		if (TraceShot())
			--Ammo;
		break;
	case ECannonType::FireBurst:
		GetWorld()->GetTimerManager().ClearTimer(BurstTimerHandle);
		currentShotInBurst = 10;
		GetWorld()->GetTimerManager().SetTimer(BurstTimerHandle, this, &ACannon::Burst, 1.0f / BurstRate / 3.0f, true);
		break;
	}

	GetWorld()->GetTimerManager().SetTimer(ReloadSpecTimerHandle, this, &ACannon::ReloadSpec, (1.0f / FireRate) * 3.0f, false);
}

bool ACannon::IsReadyToFire()
{	
	return ReadyToFire;
}

bool ACannon::IsReadyToFireSpec()
{
	return ReadyToFireSpec;
}

void ACannon::BeginPlay()
{
	Super::BeginPlay();
	Reload();
	ReloadSpec();
}

void ACannon::Reload()
{
	ReadyToFire = true;
}

void ACannon::ReloadSpec()
{
	ReadyToFireSpec = true;
}

void ACannon::Burst()
{
	if (currentShotInBurst > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("current shot = %d"), currentShotInBurst);
		GEngine->AddOnScreenDebugMessage(5, 1, FColor::Yellow, "Shot");
		if(ProjectileShot())
			--currentShotInBurst;
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(BurstTimerHandle);
		currentShotInBurst = ShotsInBurst;
		--Ammo;
	}
}

bool ACannon::ProjectileShot()
{
	GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, "Fire - projectile");
	AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,
		ProjectileSpawnPoint->GetComponentLocation(),
		ProjectileSpawnPoint->GetComponentRotation());

	if (projectile)
	{
		projectile->Start();
		return true;
	}

	return false;
}

bool ACannon::TraceShot()
{
	GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, "Fire - trace");
	FHitResult hitResult;
	FCollisionQueryParams traceParams =	FCollisionQueryParams(FName(TEXT("FireTrace")), true, this);
	traceParams.bTraceComplex = true;
	traceParams.bReturnPhysicalMaterial = false;
	FVector start = ProjectileSpawnPoint->GetComponentLocation();
	FVector end = ProjectileSpawnPoint->GetForwardVector() * FireRange + start;
	if (GetWorld()->LineTraceSingleByChannel(hitResult, start, end,	ECollisionChannel::ECC_Visibility, traceParams))
	{
		DrawDebugLine(GetWorld(), start, hitResult.Location, FColor::Red, false, 0.5f, 0, 5);
		if (hitResult.GetActor())
			return true;
	}
	else
	{
		DrawDebugLine(GetWorld(), start, end, FColor::Red, false, 0.5f, 0, 5);
	}
	return false;
}

