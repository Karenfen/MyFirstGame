// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAmmoClass.h"
#include "Laser.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API ALaser : public ABaseAmmoClass
{
	GENERATED_BODY()
	
public:
	ALaser();
	virtual ~ALaser();
	virtual void Start() override;
	FORCEINLINE void SetLenght(float lenght);

};
