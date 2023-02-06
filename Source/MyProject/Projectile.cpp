#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	USceneComponent* sceeneCpm = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = sceeneCpm;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnMeshOverlapBegin);

	// по умолчанию устанавливпем неактивное состояние, чтобы удалялся как обычно
	_isActiveInPool = false;
}

void AProjectile::Start()
{
	GetWorld()->GetTimerManager().SetTimer(MovementTimerHandle, this, &AProjectile::Move, MoveRate, true, 0.0f);
}

void AProjectile::OnMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	UE_LOG(LogTemp, Warning, TEXT("Projectile %s collided with %s. "), *GetName(), *OtherActor->GetName());

	// если активен, то делаем не активным
	if (_isActiveInPool)
	{
		// останавливаем таймер движения
		GetWorld()->GetTimerManager().ClearTimer(MovementTimerHandle);
		// делаем неактивным
		_isActiveInPool = false;
		// скрываем
		SetActorHiddenInGame(true);
		// выключаем коллизию
		SetActorEnableCollision(false);
		// отправляем в место хранения пулла
		SetActorLocation(_poolLocation);
	}
	else // если не активен, то удаляем
	{
		this->Destroy();
	}
}

void AProjectile::Move()
{
	FVector nextPosition = GetActorLocation() + GetActorForwardVector() * MoveSpeed	* MoveRate;
	SetActorLocation(nextPosition);
}

bool AProjectile::IsActive()
{
	return _isActiveInPool;
}

void AProjectile::SetIsActive(bool state)
{
	_isActiveInPool = state;
}

void AProjectile::SetZeroLocation(FVector zeroLocation)
{
	_poolLocation = zeroLocation;
}

