
#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "ProjectileForPool.generated.h"



UCLASS()
class MYPROJECT_API AProjectileForPool : public AProjectile
{
	GENERATED_BODY()
	
public:
	AProjectileForPool();
	virtual ~AProjectileForPool();

	// ���������� ���������� �����
	void SetZeroLocation(FVector zeroLocation);
	// ��������� �� ���������� �������
	bool IsActive();
	// ������������� ���������
	void SetIsActive(bool state);

protected:
	virtual void OnMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor*
		OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool
		bFromSweep, const FHitResult& SweepResult) override;

	// ��������� ������� (������������ ��� ���)
	bool _isActiveInPool;

	// ���������� ��� ���������� �������� � �����
	FVector _poolLocation;
};
