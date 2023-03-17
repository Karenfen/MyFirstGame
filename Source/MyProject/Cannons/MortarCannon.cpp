// Fill out your copyright notice in the Description page of Project Settings.


#include "MortarCannon.h"
#include "../Rounds/PhysicsProjectile.h"
#include "../Components/PoolProjectiles.h"
#include "Components/ArrowComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"



AMortarCannon::AMortarCannon()
{
}

AMortarCannon::~AMortarCannon()
{
}

void AMortarCannon::SetAimingPoint(const FVector& point)
{
	AimingPoint = point;
}

bool AMortarCannon::ProjectileShot()
{
	APhysicsProjectile* projectile;
	// если есть пулл, запрашиваем обьект
	if (ProjectilePool)
	{
		projectile = Cast<APhysicsProjectile>(ProjectilePool->GetProjectile(ProjectileSpawnPoint->GetComponentLocation()));
		if (projectile)
			projectile->SetActorRotation(ProjectileSpawnPoint->GetComponentRotation());
	}
	else
	{
		projectile = Cast<APhysicsProjectile>(GetWorld()->SpawnActor<ABaseAmmoClass>(AmmoClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation()));
	}


	if (projectile)
	{
		if (ShootEffect)
			ShootEffect->ActivateSystem();

		if (ShootAudio)
			ShootAudio->Play();

		FeedBack();

		projectile->SetDestinationPoint(AimingPoint);
		projectile->Start();

		return true;
	}

	return false;
}
