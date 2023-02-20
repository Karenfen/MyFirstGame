// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseAmmoClass.generated.h"

UCLASS()
class MYPROJECT_API ABaseAmmoClass : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
	float Damage = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Live")
	float TimeToLive = 5.0f;

	FTimerHandle DestroyTimerHandle;

public:	
	// Sets default values for this actor's properties
	ABaseAmmoClass();
	virtual ~ABaseAmmoClass();
	UFUNCTION()
	virtual void Start();

	// установить координаты пулла
	void SetZeroLocation(const FVector& zeroLocation);
	// проверака на активность обьекта
	bool IsActive();
	// устанавливаем состояние
	void SetIsActive(bool state);

protected:
	UFUNCTION()
	virtual void Destroy_();

protected:
	// состояние обьекта (используется или нет)
	bool _isActiveInPool = false;

	// координаты для временного хранения в пулле
	FVector _poolLocation = FVector::ZeroVector;
};
