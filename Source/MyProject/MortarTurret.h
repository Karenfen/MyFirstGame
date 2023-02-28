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
	float MinYawCannon = 0.0f;		/* ����������� �������� ������� ������ */

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
	float RangeYawCannon = 0.0f;		/* �������� ������� ������ */

public:
	AMortarTurret() {};
	virtual ~AMortarTurret() {};

protected:
	virtual void RotateTurretTo(FVector TargetPosition) override;
	virtual void BeginPlay() override;

	FVector turretLocation;
};
