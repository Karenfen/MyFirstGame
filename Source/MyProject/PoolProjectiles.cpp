#include "PoolProjectiles.h"
#include "BaseAmmoClass.h"

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


ABaseAmmoClass* UPoolProjectiles::CreateProjectile()
{
	// создаём новый обьект в нулевой координате
	ABaseAmmoClass* newProjectile = GetWorld()->SpawnActor<ABaseAmmoClass>(ProjectileClass, ZeroLocation, FRotator());
	if (newProjectile)
	{
		// выключаем коллизию
		newProjectile->SetActorEnableCollision(false);

		// задаём ему координуты для возвращения
		newProjectile->SetZeroLocation(ZeroLocation);
	}

	return newProjectile;
}


ABaseAmmoClass* UPoolProjectiles::GetProjectile(FVector toPosition)
{
	ABaseAmmoClass* projectileToGet = nullptr;
	// ищем в пулле свободный проджектайл
	for (ABaseAmmoClass* object : Pool)
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
		//Pool.Add(projectileToGet);
		// задаём позицию
		projectileToGet->SetActorLocation(toPosition);

		return projectileToGet;
	}
	// делаем его активным
	projectileToGet->SetIsActive(true);
	// задаём позицию
	projectileToGet->SetActorLocation(toPosition);

	return projectileToGet;
}
