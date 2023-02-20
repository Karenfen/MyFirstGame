// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAmmoClass.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ABaseAmmoClass::ABaseAmmoClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* sceeneCpm = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = sceeneCpm;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
}

ABaseAmmoClass::~ABaseAmmoClass()
{

}

void ABaseAmmoClass::Start()
{
	GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, this, &ABaseAmmoClass::Destroy_, TimeToLive, false);
	
	Mesh->SetHiddenInGame(false);
}

void ABaseAmmoClass::SetZeroLocation(const FVector& zeroLocation)
{
	_poolLocation = zeroLocation;
}

bool ABaseAmmoClass::IsActive()
{
	return _isActiveInPool;
}

void ABaseAmmoClass::SetIsActive(bool state)
{
	_isActiveInPool = state;
}

void ABaseAmmoClass::Destroy_()
{
	// если активен, то делаем не активным
	if (_isActiveInPool)
	{
		// делаем неактивным
		_isActiveInPool = false;
		// скрываем
		Mesh->SetHiddenInGame(true);
		// отправляем в место хранения пулла
		SetActorLocation(_poolLocation);
	}
	else // если не активен, то удаляем
	{
		Destroy();
	}
}
