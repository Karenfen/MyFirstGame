#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameStruct.generated.h"

class AActor;

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

USTRUCT()
struct FDamageData
{
	GENERATED_BODY()

	UPROPERTY()
	float DamageValue;

	UPROPERTY()
	AActor* Instigator;

	UPROPERTY()
	AActor* DamageMaker;
};

FVector CalculateBezierPoint(float t, const FVector& P0, const FVector& P1, const FVector& P2);