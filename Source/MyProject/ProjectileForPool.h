
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

	// установить координаты пулла
	void SetZeroLocation(FVector zeroLocation);
	// проверака на активность обьекта
	bool IsActive();
	// устанавливаем состояние
	void SetIsActive(bool state);

	virtual void Start() override;

private:
	virtual void Destroy_() override;

private:
	// состояние обьекта (используется или нет)
	bool _isActiveInPool;

	// координаты для временного хранения в пулле
	FVector _poolLocation;

};
