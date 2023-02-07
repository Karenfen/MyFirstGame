
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

protected:
	virtual void OnMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor*
		OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool
		bFromSweep, const FHitResult& SweepResult) override;

	// состояние обьекта (используется или нет)
	bool _isActiveInPool;

	// координаты для временного хранения в пулле
	FVector _poolLocation;
};
