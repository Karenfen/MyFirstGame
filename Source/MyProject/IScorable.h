#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IScorable.generated.h"

UINTERFACE(MinimalAPI)
class UIScorable : public UInterface
{
	GENERATED_BODY()
};

class MYPROJECT_API IIScorable
{
	GENERATED_BODY()

public:
	virtual float GetScores() = 0;
};
