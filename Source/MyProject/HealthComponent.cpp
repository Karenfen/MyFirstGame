#include "HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	CurrentHealth = MaxHealth;
}

void UHealthComponent::TakeDamage(FDamageData DamageData)
{
	float takedDamageValue = DamageData.DamageValue;
	CurrentHealth -= takedDamageValue;
	if (CurrentHealth <= 0)
	{
		if (OnDie.IsBound())
			OnDie.Broadcast(DamageData.Instigator);
	}
	else
	{
		if (OnDamaged.IsBound())
			OnDamaged.Broadcast(takedDamageValue);
	}
}

int UHealthComponent::GetHealth() const
{
	return CurrentHealth;
}

float UHealthComponent::GetHealthState() const
{
	return CurrentHealth / MaxHealth;
}

void UHealthComponent::AddHealth(int AddiditionalHealthValue)
{
	CurrentHealth += AddiditionalHealthValue;
	if (CurrentHealth > MaxHealth)
		CurrentHealth = MaxHealth;
}

