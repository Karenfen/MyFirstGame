#pragma once

#include "CoreMinimal.h"
#include "IMachinery.h"
#include "GameFramework/Actor.h"
#include "EnemyTurret.generated.h"

class UStaticMeshComponent;
class UArrowComponent;
class UBoxComponent;
class ACannon;
class APawn;

UCLASS()
class MYPROJECT_API AEnemyTurret : public AActor, public IIMachinery
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

	const FString BodyMeshPath = "StaticMesh'/Game/CSC/Meshes/SM_CSC_Tower1.SM_CSC_Tower1'";
	const FString TurretMeshPath = "StaticMesh'/Game/CSC/Meshes/SM_CSC_Gun1.SM_CSC_Gun1'";

public:	
	AEnemyTurret();

protected:
	UFUNCTION()
	virtual void Fire() override;
	UFUNCTION()
	virtual void SetupCannon(TSubclassOf<ACannon> newCannonClass) override;

	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	virtual void RotateTurret(float DeltaTime) override;
	void Targeting();
	bool IsPlayerInRange();
	bool CanFire();

};
