#include "PoolProjectiles.h"
#include "Projectile.h"

UPoolProjectiles::UPoolProjectiles()
{
	PrimaryComponentTick.bCanEverTick = false;

}


UPoolProjectiles::~UPoolProjectiles()
{
	// удаляем валидные обьекты 
	for (const auto& object : Pool)
	{
		if (object)
			object->Destroy();
	}
	// обнуляем пулл
	Pool.Reset();
}

void UPoolProjectiles::BeginPlay()
{
	Super::BeginPlay();

	Pool.Reset(PoolSize);
	int currentSize = 0;

	while (PoolSize > currentSize)
	{
		// добавляем в пулл новый объект
		Pool.Add(CreateProjectile());
		++currentSize;
	}
}


AProjectile* UPoolProjectiles::CreateProjectile()
{
	// создаём новый обьект в нулевой координате
	AProjectile* newProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ZeroLocation, FRotator());
	if (newProjectile)
	{
		// скрываем
		newProjectile->SetActorHiddenInGame(true);

		// выключаем коллизию
		newProjectile->SetActorEnableCollision(false);

		// задаём ему координуты для возвращения
		newProjectile->SetZeroLocation(ZeroLocation);
	}

	return newProjectile;
}


AProjectile* UPoolProjectiles::GetProjectile(FVector toPosition)
{
	AProjectile* projectileToGet = nullptr;
	// ищем в пулле свободный проджектайл
	for (AProjectile* object : Pool)
	{
		if (!IsValid(object))
		{
			// если указатель не валиден, то создаём новый объект
			projectileToGet = CreateProjectile();
			object = projectileToGet;
			break;
		}

		if (!object->IsActive())
		{
			// если в пуллу есть не активный проджектайл, то мы нашли нужный
			projectileToGet = object;
			break;
		}
	}
	// если нет свободных, создаём новый и добавляем в пулл
	if (projectileToGet == nullptr)
	{
		projectileToGet = CreateProjectile();
		Pool.Add(projectileToGet);
	}
	// делаем его активным
	projectileToGet->SetIsActive(true);
	// задаём позицию
	projectileToGet->SetActorLocation(toPosition);
	// включаем коллизию
	projectileToGet->SetActorEnableCollision(true);
	// делаем видимым
	projectileToGet->SetActorHiddenInGame(false);

	return projectileToGet;
}
