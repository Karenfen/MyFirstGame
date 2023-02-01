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
}

void ATankFactory::BeginPlay()
{
	Super::BeginPlay();

	if (LinkedMapLoader)
		LinkedMapLoader->SetIsActivated(false);

	FTimerHandle _targetingTimerHandle;
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

	if (LinkedMapLoader)
		LinkedMapLoader->SetIsActivated(true);

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

	for (int index = 0; index < activeTanks.Num(); ++index)
	{
		if (!(activeTanks[index]))
		{
			// если танк уничтожен, то добавляем его индекс в массив
			indexesDestroyedTanks.Add(index);
		}
	}

	// проходимся с конца массива для избежания неправильного доступа по индексу
	for (int index = indexesDestroyedTanks.Num() - 1; index >= 0; --index)
	{
		// удаляем невалидный танк из списка активных танков
		activeTanks.RemoveAt(index);
	}
}

