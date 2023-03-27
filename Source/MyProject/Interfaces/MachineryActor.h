// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "../GameStruct.h"
#include "DamageTaker.h"
#include "MachineryActor.generated.h"


class UStaticMeshComponent;
class UArrowComponent;
class UBoxComponent;
class ACannon;
class UHealthComponent;


UCLASS()
class MYPROJECT_API AMachineryActor : public APawn, public IDamageTaker
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
	UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	TSubclassOf<ACannon> CannonClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Rotation")
	float TurretRotationInterpolationKey = 0.5f;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Effects")
	class UAudioComponent* AudioResupply;

	UPROPERTY()
	ACannon* Cannon;

public:	
	// Sets default values for this actor's properties
	AMachineryActor();
	virtual ~AMachineryActor() {};

	virtual void Fire();
	virtual void Resupply(uint8 numberRounds = 10);
	UFUNCTION()
	virtual void RotateTurretTo(FVector TargetPosition);
	FORCEINLINE FVector GetTurretForwardVector() { return TurretMesh->GetForwardVector(); };
	FVector GetEyesPosition();
	FORCEINLINE TSubclassOf<ACannon> CurentCannonClass() { return CannonClass; };
	UFUNCTION()
	virtual void SetupCannon(TSubclassOf<ACannon> newCannonClass);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void DamageTaked(int DamageValue);
	UFUNCTION()
	virtual void TakeDamage_(FDamageData DamageData) override;
	UFUNCTION()
	virtual void Die(AActor* killer);
	UFUNCTION()
	virtual void Destroyed();
};
