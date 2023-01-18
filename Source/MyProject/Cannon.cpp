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

	if (!CheckAmmo())
	{
		return;
	}

	ReadyToFire = false;

	if (Type == ECannonType::FireProjectile)
	{
		GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, "Fire - projectile");
	}
	else if(Type == ECannonType::FireTrace)
	{
		GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, "Fire - trace");
	}
		
	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this,	&ACannon::Reload, 1 / FireRate, false);
}

void ACannon::FireSpecial()
{
	if (!ReadyToFire)
	{
		return;
	}

	if (!CheckAmmo())
	{
		return;
	}

	ReadyToFire = false;

	if (Type == ECannonType::FireProjectile)
	{
		GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, "Fire - projectile special");
	}
	else if (Type == ECannonType::FireTrace)
	{
		GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, "Fire - tracespecial");
	}

	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ACannon::Reload, 1 / FireRate, false);
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

bool ACannon::CheckAmmo()
{
	if (Ammo == 0)
	{
		GEngine->AddOnScreenDebugMessage(5, 1, FColor::Red, "Ammo is empty");
		return false;
	}

	--Ammo;

	return true;
}


