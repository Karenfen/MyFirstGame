// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Interfaces/TankPawn.h"
#include "PlayerTankPawn.generated.h"

class UCameraComponent;
class USpringArmComponent;


UCLASS()
class MYPROJECT_API APlayerTankPawn : public ATankPawn
{
	GENERATED_BODY()

	DECLARE_EVENT(APlayerTankPawn, FOnDie)

public:
	FOnDie OnDie;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UArrowComponent* FRArrow;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UArrowComponent* RRArrow;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UCameraComponent* Camera;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Effects")
	UAudioComponent* AudioChangeCannon;
	
	UPROPERTY()
	class ATankPlayerController* TankController;
	
	UPROPERTY()
	ACannon* SecondCannon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon")
	TSubclassOf<ACannon> SecondCannonClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Scores")
	int CurrentScores = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Scores")
	int MaxScores = 1000000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<class UMain_HUD_Widget> HUD_widget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Rotation")
	float TankRotationInterpolationKey = 0.5f;

	float _TurretDirX = 0.0f;
	float _TurretDirY = 0.0f;

public:
	APlayerTankPawn();
	virtual ~APlayerTankPawn() {};
	virtual void Fire() override;
	virtual void Resupply(uint8 numberRounds = 10) override;
	virtual void Tick(float DeltaTime) override;
	virtual void FellOutOfWorld(const class UDamageType& dmgType);
	void FireSpecial();
	void EnemyDestroyed(AActor* destroyedObject);
	void SwitchCannon();
	void AddCannon(TSubclassOf<ACannon> newCannonClass);
	virtual void SetupCannon(TSubclassOf<ACannon> newCannonClass) override;

	// Function for saving
	FPlayerTankState GetState();

protected:
	virtual void BeginPlay() override;
	virtual void Die(AActor* killer) override;
	virtual void DamageTaked(int DamageValue) override;
	virtual void Rotate(float DeltaTime) override;
	void RotateBodyTo(const FVector& target);
	void SetupSecondCannon(TSubclassOf<ACannon> newCannonClass);

	// Functions for saving/loading
	void SetStateAfterInit();
	void SetStateBeforeInit();
	void UpdateState();

	// functions for update HUD
	void UpdateHUD();
	void UpdateHealteHUD();
	void UpdateScoresHUD();
	void UpdateCCAmmoHUD();
	void UpdateSCAmmoHUD();
	void UpdateCCIconHUD();
	void UpdateSCIconHUD();

private:
	class UMain_HUD_Widget* HUD {nullptr};
	FPlayerTankState state;
};
