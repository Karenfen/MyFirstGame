#include "PoolProjectiles.h"
#include "BaseAmmoClass.h"

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


ABaseAmmoClass* UPoolProjectiles::CreateProjectile()
{
	// ������ ����� ������ � ������� ����������
	ABaseAmmoClass* newProjectile = GetWorld()->SpawnActor<ABaseAmmoClass>(ProjectileClass, ZeroLocation, FRotator());
	if (newProjectile)
	{
		// ��������� ��������
		newProjectile->SetActorEnableCollision(false);

		// ����� ��� ���������� ��� �����������
		newProjectile->SetZeroLocation(ZeroLocation);
	}

	return newProjectile;
}


ABaseAmmoClass* UPoolProjectiles::GetProjectile(FVector toPosition)
{
	ABaseAmmoClass* projectileToGet = nullptr;
	// ���� � ����� ��������� �����������
	for (ABaseAmmoClass* object : Pool)
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
		//Pool.Add(projectileToGet);
		// ����� �������
		projectileToGet->SetActorLocation(toPosition);

		return projectileToGet;
	}
	// ������ ��� ��������
	projectileToGet->SetIsActive(true);
	// ����� �������
	projectileToGet->SetActorLocation(toPosition);

	return projectileToGet;
}
