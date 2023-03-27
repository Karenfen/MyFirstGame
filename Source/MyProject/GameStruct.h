#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameStruct.generated.h"

class AActor;
class ACannon;

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

UENUM(BlueprintType)
enum class ESaveSlots : uint8
{
	PlayerTemp = 0 UMETA(DisplayName = "Player temp slot"),
	Game = 1 UMETA(DisplayName = "Game slot")
};

USTRUCT()
struct FPlayerTankState
{
	GENERATED_BODY()

	UPROPERTY()
		TSubclassOf<ACannon> FirstCannon{nullptr};

	UPROPERTY()
		int FCAmmo = -1;

	UPROPERTY()
		TSubclassOf<ACannon> SecondCannon{nullptr};

	UPROPERTY()
		int SCAmmo = -1;

	UPROPERTY()
		int CurrentHealth = -1;

	UPROPERTY()
		int Scores = -1;
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
	uint16 DamageValue;

	UPROPERTY()
	AActor* Instigator;

	UPROPERTY()
	AActor* DamageMaker;
};

FVector CalculateBezierPoint(float t, const FVector& P0, const FVector& P1, const FVector& P2);

namespace Bezier
{
	const float t_star = 0.0f;
	const float t_end = 1.0f;
};