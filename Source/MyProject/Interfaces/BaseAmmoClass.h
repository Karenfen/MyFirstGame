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

	// ���������� ���������� �����
	void SetZeroLocation(const FVector& zeroLocation);
	// ��������� �� ���������� �������
	bool IsActive();
	// ������������� ���������
	void SetIsActive(bool state);

protected:
	UFUNCTION()
	virtual void Destroy_();

protected:
	// ��������� ������� (������������ ��� ���)
	bool _isActiveInPool = false;

	// ���������� ��� ���������� �������� � �����
	FVector _poolLocation = FVector::ZeroVector;
};
