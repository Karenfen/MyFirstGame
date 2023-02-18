
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

	virtual void Start() override;

private:
	virtual void Destroy_() override;

private:
	// ��������� ������� (������������ ��� ���)
	bool _isActiveInPool;

	// ���������� ��� ���������� �������� � �����
	FVector _poolLocation;

};
