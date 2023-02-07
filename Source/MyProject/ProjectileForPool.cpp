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

void AProjectileForPool::OnMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AActor* owner = GetOwner();
	AActor* ownerByOwner = owner != nullptr ? owner->GetOwner() : nullptr;

	if (OtherActor != owner && OtherActor != ownerByOwner)
	{
		IDamageTaker* damageTakerActor = Cast<IDamageTaker>(OtherActor);
		if (damageTakerActor)
		{
			FDamageData damageData;
			damageData.DamageValue = Damage;
			damageData.Instigator = ownerByOwner;
			damageData.DamageMaker = this;
			damageTakerActor->TakeDamage(damageData);
		}

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
}
