#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DamageTaker.generated.h"

struct  FDamageData;

UINTERFACE(MinimalAPI)
class UDamageTaker : public UInterface
{
	GENERATED_BODY()
};

class MYPROJECT_API IDamageTaker
{
	GENERATED_BODY()

public:
	virtual void TakeDamage(FDamageData DamageData) = 0;
};
