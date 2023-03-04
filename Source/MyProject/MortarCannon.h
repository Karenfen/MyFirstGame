// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cannon.h"
#include "MortarCannon.generated.h"


UCLASS()
class MYPROJECT_API AMortarCannon : public ACannon
{
	GENERATED_BODY()

public:
	AMortarCannon();
	virtual ~AMortarCannon() override;
	void SetAimingPoint(const FVector& point);

protected:
	virtual bool ProjectileShot() override;

private:
	FVector AimingPoint = FVector::ZeroVector;
};
