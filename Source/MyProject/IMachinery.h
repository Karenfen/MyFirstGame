#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IMachinery.generated.h"

class UStaticMeshComponent;
class UArrowComponent;
class ACannon;

UINTERFACE(MinimalAPI)
class UIMachinery : public UInterface
{
	GENERATED_BODY()
};

class MYPROJECT_API IIMachinery
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void Fire() = 0;
	UFUNCTION()
	virtual void SetupCannon(TSubclassOf<ACannon> newCannonClass) = 0;

protected:
	virtual void RotateTurret(float DeltaTime) = 0;
};
