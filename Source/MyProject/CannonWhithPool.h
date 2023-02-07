#pragma once

#include "CoreMinimal.h"
#include "Cannon.h"
#include "CannonWhithPool.generated.h"


UCLASS()
class MYPROJECT_API ACannonWhithPool : public ACannon
{
	GENERATED_BODY()
	
protected:
	// добавляем компонент пулл проджектайлов
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UPoolProjectiles* ProjectilePool;

public:
	ACannonWhithPool();
	virtual ~ACannonWhithPool();

protected:
	virtual bool ProjectileShot() override;
};
