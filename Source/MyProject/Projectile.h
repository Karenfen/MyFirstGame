#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class MYPROJECT_API AProjectile : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* Mesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float MoveSpeed = 500;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float MoveRate = 0.005f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
		float Damage = 1;
	FTimerHandle MovementTimerHandle;
	
public:	
	AProjectile();
	void Start();
	// установить координаты пулла
	void SetZeroLocation(FVector zeroLocation);
	// проверака на активность обьекта
	bool IsActive();
	// устанавливаем состояние
	void SetIsActive(bool state);

protected:
	UFUNCTION()
		void OnMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor*
			OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool
			bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void Move();

	// состояние обьекта (используется или нет)
	bool _isActiveInPool;

	// координаты для временного хранения в пулле
	FVector _poolLocation;
};
