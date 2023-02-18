#include "ProjectileForPool.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/EngineTypes.h"
#include "DamageTaker.h"
#include "GameStruct.h"

AProjectileForPool::AProjectileForPool()
{
	// по умолчанию устанавливпем неактивное состояние, чтобы удалялся как обычно
	_isActiveInPool = false;
}

AProjectileForPool::~AProjectileForPool()
{

}

void AProjectileForPool::SetZeroLocation(FVector zeroLocation)
{
	_poolLocation = zeroLocation;
}

bool AProjectileForPool::IsActive()
{
	return _isActiveInPool;
}


void AProjectileForPool::SetIsActive(bool state)
{
	_isActiveInPool = state;
}

void AProjectileForPool::Start()
{
	Super::Start();

	Mesh->SetHiddenInGame(false);
	SetActorEnableCollision(true);
}

void AProjectileForPool::Destroy_()
{
	// если активен, то делаем не активным
	if (_isActiveInPool)
	{
		// останавливаем таймер движения
		GetWorld()->GetTimerManager().ClearTimer(MovementTimerHandle);
		// делаем неактивным
		_isActiveInPool = false;
		// скрываем
		Mesh->SetHiddenInGame(true);
		// выключаем коллизию
		SetActorEnableCollision(false);
		// отправляем в место хранения пулла
		SetActorLocation(_poolLocation);
	}
	else // если не активен, то удаляем
	{
		Destroy();
	}
}
