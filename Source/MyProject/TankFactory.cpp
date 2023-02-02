#include "TankFactory.h"
#include "TimerManager.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SceneComponent.h"
#include "HealthComponent.h"
#include "TankPawn.h"
#include "MapLoader.h"
#include "Engine/StaticMesh.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"



ATankFactory::ATankFactory()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = sceneComp;

	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Building	Mesh"));
	BuildingMesh->SetupAttachment(sceneComp);

	TankSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Cannon setup	point"));
	TankSpawnPoint->AttachToComponent(sceneComp, FAttachmentTransformRules::KeepRelativeTransform);
	
	HitCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Hit collider"));
	HitCollider->SetupAttachment(sceneComp);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health	component"));
	HealthComponent->OnDie.AddUObject(this, &ATankFactory::Die);
	HealthComponent->OnDamaged.AddUObject(this, &ATankFactory::DamageTaked);

	// визуальный эффект для разрушения
	DestroyEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Destroy Effect"));
	DestroyEffect->SetupAttachment(sceneComp);
	DestroyEffect->SetAutoActivate(false); // выключаем автозапуск

	// аудио эффект для разрушения
	DestroyAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("Destroy Audio"));
	DestroyAudio->SetupAttachment(sceneComp);
	DestroyAudio->SetAutoActivate(false); // выключаем автозапуск

}

void ATankFactory::BeginPlay()
{
	Super::BeginPlay();

	if (LinkedMapLoader)
		LinkedMapLoader->SetIsActivated(false);

	// запускаем таймер создания танков
	GetWorld()->GetTimerManager().SetTimer(_targetingTimerHandle, this, &ATankFactory::SpawnNewTank, SpawnTankRate, true, SpawnTankRate);
}

void ATankFactory::TakeDamage(FDamageData DamageData)
{
	HealthComponent->TakeDamage(DamageData);
}

void ATankFactory::Die(AActor* killer)
{
	// если наш убийца - это игрок, засчитываем ему очки
	if (killer == GetWorld()->GetFirstPlayerController()->GetPawn())
	{
		ATankPawn* player = Cast<ATankPawn>(killer);
		if (player)
			player->EnemyDestroyed(this);
	}

	// активируем переход, если он есть
	if (LinkedMapLoader)
		LinkedMapLoader->SetIsActivated(true);

	// включаем звук разрушения, если он есть
	if (DestroyAudio)
		DestroyAudio->Play();

	// если есть модель разрушенного здания...
	if (BuildingDestroyedMesh)
	{
		// выключаем таймер на создание танков
		GetWorld()->GetTimerManager().ClearTimer(_targetingTimerHandle);
		// устанавливаем новую модельку
		BuildingMesh->SetStaticMesh(BuildingDestroyedMesh);

		// если есть визуальный эффект, включаем его 
		if (DestroyEffect)
			DestroyEffect->ActivateSystem();

		// если есть компонент здоровья, отключаем коннекты
		if (HealthComponent)
		{
			HealthComponent->OnDie.Clear();
			HealthComponent->OnDamaged.Clear();
		}
	}
	else // если нет модели разрушения, просто уничтожаем 
		Destroy();
}

void ATankFactory::DamageTaked(float DamageValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Factory %s taked damage:%f Health:%f"), *GetName(), DamageValue, HealthComponent->GetHealth());
}

void ATankFactory::SpawnNewTank()
{
	// делаем проверку активных танков
	CheckTanks();

	// проверяем не достигнут ли предел активных танков
	if (activeTanks.Num() >= MaxTankNum)
		return;

	FTransform spawnTransform(TankSpawnPoint->GetComponentRotation(), TankSpawnPoint->GetComponentLocation(), FVector(1));
	ATankPawn* newTank = GetWorld()->SpawnActorDeferred<ATankPawn>(SpawnTankClass, spawnTransform, this, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	newTank->SetPatrollingPoints(TankWayPoints);
	
	UGameplayStatics::FinishSpawningActor(newTank, spawnTransform);

	// после завершения инициализации добавляем новый танк в список активных
	activeTanks.Add(newTank);
}

void ATankFactory::CheckTanks()
{
	// массив для хранения индексов невалидных указателей на танки
	TArray<int> indexesDestroyedTanks{};
	//indexesDestroyedTanks.SetNum(0);

	for (int index = 0; index < activeTanks.Num(); ++index)
	{
		// если танк невалиден или помечен на удаление, то добавляем его индекс в массив
		if (!activeTanks[index])
			indexesDestroyedTanks.Add(index);
		else if (activeTanks[index]->IsPendingKill())
			indexesDestroyedTanks.Add(index);
	}

	// проходимся с конца массива для избежания неправильного доступа по индексу
	for (int index = indexesDestroyedTanks.Num() - 1; index >= 0; --index)
	{
		// удаляем невалидный танк из списка активных танков
		activeTanks.RemoveAt(indexesDestroyedTanks[index]);
	}
}

