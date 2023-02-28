#pragma once

#include "CoreMinimal.h"
#include "DamageTaker.h"
#include "IScorable.h"
#include "GameStruct.h"
#include "MachineryActor.h"
#include "EnemyTurret.generated.h"


struct FTimerHandle;

UCLASS()
class MYPROJECT_API AEnemyTurret : public AMachineryActor, public IIScorable
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	float RechargeSpeed = 5.0f;

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

	FTimerHandle RechargeTimerHandle;
	FTimerHandle _targetingTimerHandle;
	bool CannonIsReady = true;

public:	
	AEnemyTurret();
	virtual ~AEnemyTurret() {};

protected:
	virtual void Fire() override;
	virtual void Die(AActor* killer) override;
	virtual int GetScores() override { return Scores; };
	virtual void BeginPlay() override;
	void Targeting();
	bool IsPlayerInRange();
	bool CanFire();
	void RechargeCannon();
	bool IsPlayerSeen();
};
