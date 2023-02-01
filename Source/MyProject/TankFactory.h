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
	float Scores = 150.0f;

public:	
	ATankFactory();

	UFUNCTION()
	void TakeDamage(FDamageData DamageData);

	UFUNCTION()
	virtual float GetScores() override { return Scores; };

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
};
