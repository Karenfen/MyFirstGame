#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageTaker.h"
#include "GameStruct.h"
#include "IScorable.h"
#include "TankFactory.generated.h"


class ATankPawn;
class ATargetPoint;

UCLASS()
class MYPROJECT_API ATankFactory : public AActor, public IDamageTaker, public IIScorable /* для получения очков за уничтожение */
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent* BuildingMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UArrowComponent* TankSpawnPoint;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UBoxComponent* HitCollider;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UHealthComponent* HealthComponent;

	// визуальный эффект разрушения здания
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Effects")
	class UParticleSystemComponent* DestroyEffect;

	// аудио эффект разрушения здания
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Effects")
	class UAudioComponent* DestroyAudio;

	// указатель на загрузчик для перехода
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Linked")
	class AMapLoader* LinkedMapLoader;

	// новая модель при разрушении
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Destroyed mesh")
	class UStaticMesh* BuildingDestroyedMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn tanks params")
	TSubclassOf<ATankPawn> SpawnTankClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Spawn tanks params")
	float SpawnTankRate = 1.0f;

	//ограничение колличества активных танков
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Spawn tanks params")
	int MaxTankNum = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn tanks params")
	TArray<ATargetPoint*> TankWayPoints;

	//очки за уничтожение
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scores")
	int Scores = 150;

public:	
	ATankFactory();
	virtual void TakeDamage_(FDamageData DamageData) override;

	UFUNCTION()
	virtual int GetScores() override { return Scores; };

protected:
	virtual void BeginPlay() override;
	void SpawnNewTank();
	//проверка целостности танков
	void CheckTanks();

	UFUNCTION()
	void Die(AActor* killer);

	UFUNCTION()
	void DamageTaked(float DamageValue);
	
	//указатели на активные танки
	TArray<ATankPawn*> activeTanks{};
	// вынесем таймер для его выключения 
	FTimerHandle _targetingTimerHandle;

};
