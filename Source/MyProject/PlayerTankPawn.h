// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankPawn.h"
#include "PlayerTankPawn.generated.h"

class UCameraComponent;
class USpringArmComponent;


UCLASS()
class MYPROJECT_API APlayerTankPawn : public ATankPawn
{
	GENERATED_BODY()

protected:
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
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Scores")
	int CurrentScores = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Scores")
	int MaxScores = 1000000;


	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Component")
	class UMain_HUD_Widget* HUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<class UMain_HUD_Widget> HUD_widget;

	float _TurretDirX = 0.0f;
	float _TurretDirY = 0.0f;

public:
	APlayerTankPawn();
	virtual ~APlayerTankPawn() {};
	virtual void Fire() override;
	virtual void Resupply(uint8 numberRounds) override;
	virtual void Tick(float DeltaTime) override;
	void FireSpecial();
	void EnemyDestroyed(AActor* destroyedObject);
	void SwitchCannon();
	virtual void SetupCannon(TSubclassOf<ACannon> newCannonClass) override;
	FORCEINLINE void SetTurretDirX(float AxisValue) { _TurretDirX = AxisValue; };
	FORCEINLINE void SetTurretDirY(float AxisValue) { _TurretDirY = AxisValue; };

protected:
	virtual void BeginPlay() override;
	virtual void Die(AActor* killer) override;
	virtual void DamageTaked(int DamageValue) override;

	void UpdateHUD();
	void UpdateHealteHUD();
	void UpdateScoresHUD();
	void UpdateCCAmmoHUD();
	void UpdateSCAmmoHUD();
	void UpdateCCIconHUD();
	void UpdateSCIconHUD();
};
