#include "Cannon.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "Engine/Engine.h"

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
		SingleShot();
		break;
	case ECannonType::FireTrace:
		GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, "Fire - trace");
		SingleShot();
		break;
	case ECannonType::FireBurst:
		GetWorld()->GetTimerManager().SetTimer(BurstTimerHandle, this, &ACannon::Burst, 1 / BurstRate, true);
		GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, "Fire - burst");
		return;
		break;
	}
		
	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this,	&ACannon::Reload, 1 / FireRate, false);
}

void ACannon::FireSpecial()
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
		GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, "Fire - projectile special");
		SingleShot();
		break;
	case ECannonType::FireTrace:
		GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, "Fire - trace special");
		SingleShot();
		break;
	case ECannonType::FireBurst:
		GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, "Fire - burst special");
		GetWorld()->GetTimerManager().SetTimer(AutoShotsTimerHandle, this, &ACannon::AutoShots, 1 / BurstRate, true);
		return;
		break;
	}

	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ACannon::Reload, 1 / FireRate, false);
}

void ACannon::StopAutoShots()
{
	GetWorld()->GetTimerManager().ClearTimer(AutoShotsTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ACannon::Reload, 1 / FireRate * 2, false);
}

bool ACannon::IsReadyToFire()
{	
	return ReadyToFire;
}

void ACannon::BeginPlay()
{
	Super::BeginPlay();
	Reload();
}

void ACannon::Reload()
{
	ReadyToFire = true;
}

void ACannon::Burst()
{
	if (currentShotInBurst > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("current shot = %d"), currentShotInBurst);
		GEngine->AddOnScreenDebugMessage(5, 1, FColor::Yellow, "Shot");
		--currentShotInBurst;
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(BurstTimerHandle);
		currentShotInBurst = ShotsInBurst;
		--Ammo;
		GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ACannon::Reload, 1 / FireRate, false);
	}
}

void ACannon::AutoShots()
{
	if (Ammo > 0)
		SingleShot();
	else
	{
		StopAutoShots();
		GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ACannon::Reload, 1 / FireRate, false);
	}
}

void ACannon::SingleShot()
{
	UE_LOG(LogTemp, Warning, TEXT("shot"));
	--Ammo;
}


