// Fill out your copyright notice in the Description page of Project Settings.


#include "Laser.h"

ALaser::ALaser()
{
	PrimaryActorTick.bCanEverTick = false;
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
}

ALaser::~ALaser()
{

}

void ALaser::Start()
{
	Super::Start(); 
	SetActorHiddenInGame(false);
}

FORCEINLINE void ALaser::SetLenght(float lenght)
{
	FVector newScale = Mesh->GetRelativeScale3D();
	newScale.X = lenght;
	
	Mesh->SetRelativeScale3D(newScale);
}
