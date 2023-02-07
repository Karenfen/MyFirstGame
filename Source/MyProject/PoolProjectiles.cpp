#include "PoolProjectiles.h"
#include "ProjectileForPool.h"

UPoolProjectiles::UPoolProjectiles()
{
	PrimaryComponentTick.bCanEverTick = false;

}


UPoolProjectiles::~UPoolProjectiles()
{
	// ������� �������� ������� 
	for (const auto& object : Pool)
	{
		if (object)
			object->Destroy();
	}
	// �������� ����
	Pool.Reset();
}

void UPoolProjectiles::BeginPlay()
{
	Super::BeginPlay();

	Pool.Reset(PoolSize);
	int currentSize = 0;

	while (PoolSize > currentSize)
	{
		// ��������� � ���� ����� ������
		Pool.Add(CreateProjectile());
		++currentSize;
	}
}


AProjectileForPool* UPoolProjectiles::CreateProjectile()
{
	// ������ ����� ������ � ������� ����������
	AProjectileForPool* newProjectile = GetWorld()->SpawnActor<AProjectileForPool>(ProjectileClass, ZeroLocation, FRotator());
	if (newProjectile)
	{
		// ��������
		newProjectile->SetActorHiddenInGame(true);

		// ��������� ��������
		newProjectile->SetActorEnableCollision(false);

		// ����� ��� ���������� ��� �����������
		newProjectile->SetZeroLocation(ZeroLocation);
	}

	return newProjectile;
}


AProjectileForPool* UPoolProjectiles::GetProjectile(FVector toPosition)
{
	AProjectileForPool* projectileToGet = nullptr;
	// ���� � ����� ��������� �����������
	for (AProjectileForPool* object : Pool)
	{
		if (!IsValid(object))
		{
			// ���� ��������� �� �������, �� ������ ����� ������
			projectileToGet = CreateProjectile();
			object = projectileToGet;
			break;
		}

		if (!object->IsActive())
		{
			// ���� � ����� ���� �� �������� �����������, �� �� ����� ������
			projectileToGet = object;
			break;
		}
	}
	// ���� ��� ���������, ������ ����� � ��������� � ����
	if (projectileToGet == nullptr)
	{
		projectileToGet = CreateProjectile();
		Pool.Add(projectileToGet);
	}
	// ������ ��� ��������
	projectileToGet->SetIsActive(true);
	// ����� �������
	projectileToGet->SetActorLocation(toPosition);
	// �������� ��������
	projectileToGet->SetActorEnableCollision(true);
	// ������ �������
	projectileToGet->SetActorHiddenInGame(false);

	return projectileToGet;
}
