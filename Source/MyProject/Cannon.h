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

	// ��������� ��������� ���� �������������
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UPoolProjectiles* ProjectilePool;

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
		int maxAmmo = 50;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo")
		int Ammo = 5;

	FTimerHandle ReloadTimerHandle;
	FTimerHandle BurstTimerHandle;
	FTimerHandle ReloadSpecTimerHandle;
	bool ReadyToFire = false;
	bool ReadyToFireSpec = false;
	uint8 currentShotInBurst = ShotsInBurst;
	
public:	
	ACannon();
	void Fire();
	void FireSpecial();
	bool IsReadyToFire();
	bool IsReadyToFireSpec();
	void Resupply(uint8 numberRounds);
	ECannonType GetType();

protected:
	virtual void BeginPlay() override;
	void Reload();
	void ReloadSpec();
	void Burst();
	bool ProjectileShot();
	void TraceShot();
};

