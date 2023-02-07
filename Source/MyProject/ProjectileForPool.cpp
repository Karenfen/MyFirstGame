#include "ProjectileForPool.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/EngineTypes.h"

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

void AProjectileForPool::OnMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Projectile %s collided with %s. "), *GetName(), *OtherActor->GetName());

	// ���� �������, �� ������ �� ��������
	if (_isActiveInPool)
	{
		// ������������� ������ ��������
		GetWorld()->GetTimerManager().ClearTimer(MovementTimerHandle);
		// ������ ����������
		_isActiveInPool = false;
		// ��������
		SetActorHiddenInGame(true);
		// ��������� ��������
		SetActorEnableCollision(false);
		// ���������� � ����� �������� �����
		SetActorLocation(_poolLocation);
	}
	else // ���� �� �������, �� �������
	{
		this->Destroy();
	}
}
