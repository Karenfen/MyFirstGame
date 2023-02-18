#include "ProjectileForPool.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/EngineTypes.h"
#include "DamageTaker.h"
#include "GameStruct.h"

AProjectileForPool::AProjectileForPool()
{
	// �� ��������� ������������� ���������� ���������, ����� �������� ��� ������
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
	// ���� �������, �� ������ �� ��������
	if (_isActiveInPool)
	{
		// ������������� ������ ��������
		GetWorld()->GetTimerManager().ClearTimer(MovementTimerHandle);
		// ������ ����������
		_isActiveInPool = false;
		// ��������
		Mesh->SetHiddenInGame(true);
		// ��������� ��������
		SetActorEnableCollision(false);
		// ���������� � ����� �������� �����
		SetActorLocation(_poolLocation);
	}
	else // ���� �� �������, �� �������
	{
		Destroy();
	}
}
