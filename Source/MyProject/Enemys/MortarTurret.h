#pragma once

#include "CoreMinimal.h"
#include "EnemyTurret.h"
#include "MortarTurret.generated.h"


UCLASS()
class MYPROJECT_API AMortarTurret : public AEnemyTurret
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
	float MinYawCannon = 0.0f;		/* минимальное значение наклона орудия */

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
	float RangeYawCannon = 0.0f;		/* диапазон наклона орудия */

public:
	AMortarTurret() {};
	virtual ~AMortarTurret() {};
	virtual void RotateTurretTo(FVector TargetPosition) override;
protected:
	virtual void BeginPlay() override;
	virtual void Fire() override;

	FVector turretLocation = FVector::ZeroVector;
};
