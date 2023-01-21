#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameStruct.h"
#include "Projectile.h"
#include "Cannon.generated.h"

class UArrowComponent;

UCLASS()
class MYPROJECT_API ACannon : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UArrowComponent* ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		float FireRate = 1.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		float BurstRate = 10.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		float FireRange = 1000.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		float FireDamage = 1.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		ECannonType Type = ECannonType::FireProjectile;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		uint8 ShotsInBurst = 3;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		float BurstDamage = FireDamage / ShotsInBurst;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		TSubclassOf<AProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo")
		int Ammo = 10;

	FTimerHandle ReloadTimerHandle;
	FTimerHandle BurstTimerHandle;
	FTimerHandle AutoShotsTimerHandle;
	bool ReadyToFire = false;
	uint8 currentShotInBurst = ShotsInBurst;
	
public:	
	ACannon();
	void Fire();
	void FireSpecial();
	void StopAutoShots();
	bool IsReadyToFire();

protected:
	virtual void BeginPlay() override;
	void Reload();
	void Burst();
	void AutoShots();
	void SingleShot();
	void ProjectileShot();
};

