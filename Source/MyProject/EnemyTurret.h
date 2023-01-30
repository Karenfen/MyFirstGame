#pragma once

#include "CoreMinimal.h"
#include "IMachinery.h"
#include "DamageTaker.h"
#include "IScorable.h"
#include "GameFramework/Actor.h"
#include "GameStruct.h"
#include "EnemyTurret.generated.h"

class UStaticMeshComponent;
class UArrowComponent;
class UBoxComponent;
class ACannon;
class APawn;
class UHealthComponent;
struct FTimerHandle;

UCLASS()
class MYPROJECT_API AEnemyTurret : public AActor, public IIMachinery, public IDamageTaker, public IIScorable
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* BodyMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UArrowComponent* CannonSetupPoint;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UBoxComponent* HitCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	TSubclassOf<ACannon> CannonClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	float RechargeSpeed = 5.0f;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UHealthComponent* HealthComponent;

	UPROPERTY()
	ACannon* Cannon;

	UPROPERTY()
	APawn* PlayerPawn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
	float TargetingRange = 1000;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
	float TargetingSpeed = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
	float TargetingRate = 0.005f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
	float Accurency = 10;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Score")
	float Scores = 50;

	const FString BodyMeshPath = "StaticMesh'/Game/CSC/Meshes/SM_CSC_Tower1.SM_CSC_Tower1'";
	const FString TurretMeshPath = "StaticMesh'/Game/CSC/Meshes/SM_CSC_Gun1.SM_CSC_Gun1'";

	FTimerHandle RechargeTimerHandle;
	FTimerHandle _targetingTimerHandle;
	bool CannonIsReady = true;

public:	
	AEnemyTurret();

protected:
	UFUNCTION()
	virtual void Fire() override;

	UFUNCTION()
	virtual void SetupCannon(TSubclassOf<ACannon> newCannonClass) override;

	UFUNCTION()
	virtual void TakeDamage(FDamageData DamageData) override;

	UFUNCTION()
	virtual void Die(AActor* killer) override;

	UFUNCTION()
	virtual void DamageTaked(float DamageValue) override;

	UFUNCTION()
	virtual float GetScores() override { return Scores; };

private:
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	virtual void RotateTurret(float DeltaTime) override;
	void Targeting();
	bool IsPlayerInRange();
	bool CanFire();
	void RechargeCannon();
	bool IsPlayerSeen();
	FVector GetEyesPosition();
};
