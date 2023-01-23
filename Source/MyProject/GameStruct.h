#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameStruct.generated.h"

UENUM(BlueprintType)
enum class ECannonType : uint8
{
	FireProjectile = 0 UMETA(DisplayName = "Use projectile"),
	FireTrace = 1 UMETA(DisplayName = "Use trace"),
	FireBurst = 2 UMETA(DisplayName = "Use burst")
};

UENUM(BlueprintType)
enum class EAmmoBoxType : uint8
{
	CannonBox = 0 UMETA(DisplayName = "Set Cannon"),
	RoundsBox = 1 UMETA(DisplayName = "Set rounds")
};

UCLASS()
class MYPROJECT_API UGameStruct : public UObject
{
	GENERATED_BODY()
	
};
