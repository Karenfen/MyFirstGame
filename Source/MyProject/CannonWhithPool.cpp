#include "CannonWhithPool.h"
#include "PoolProjectiles.h"
#include "Components/ArrowComponent.h"
#include "ProjectileForPool.h"


ACannonWhithPool::ACannonWhithPool()
{
	// создаём пулл
	ProjectilePool = CreateDefaultSubobject<UPoolProjectiles>(TEXT("Pool Projectiles"));
}

ACannonWhithPool::~ACannonWhithPool()
{

}

bool ACannonWhithPool::ProjectileShot()
{
	GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, "Fire - projectile");

	AProjectileForPool* projectile;
	// если есть пулл, запрашиваем обьект
	if (ProjectilePool)
	{
		projectile = ProjectilePool->GetProjectile(ProjectileSpawnPoint->GetComponentLocation());
		if (projectile)
			projectile->SetActorRotation(ProjectileSpawnPoint->GetComponentRotation());
	}
	else 
	{
		projectile = GetWorld()->SpawnActor<AProjectileForPool>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());
	}


	if (projectile)
	{
		projectile->Start();
		return true;
	}

	return false;
}
