#pragma once

#include "CoreMinimal.h"
#include "GameStruct.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

	DECLARE_EVENT_OneParam(UHealthComponent, FOnDie, AActor*)
	DECLARE_EVENT_OneParam(UHealthComponent, FOnHealthChanged, float)

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health values")
	float MaxHealth = 10;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health values")
	float CurrentHealth;

public:
	FOnDie OnDie;
	FOnHealthChanged OnDamaged;

public:	
	UHealthComponent();

	void TakeDamage(FDamageData DamageData);
	float GetHealth() const;
	float GetHealthState() const;
	void AddHealth(float AddiditionalHealthValue);	
};
