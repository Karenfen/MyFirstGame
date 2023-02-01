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
	// ���� ��� ������ - ��� �����, ����������� ��� ����
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
	// ������ �������� �������� ������
	CheckTanks();

	// ��������� �� ��������� �� ������ �������� ������
	if (activeTanks.Num() >= MaxTankNum)
		return;

	FTransform spawnTransform(TankSpawnPoint->GetComponentRotation(), TankSpawnPoint->GetComponentLocation(), FVector(1));
	ATankPawn* newTank = GetWorld()->SpawnActorDeferred<ATankPawn>(SpawnTankClass, spawnTransform, this, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	newTank->SetPatrollingPoints(TankWayPoints);
	
	UGameplayStatics::FinishSpawningActor(newTank, spawnTransform);

	// ����� ���������� ������������� ��������� ����� ���� � ������ ��������
	activeTanks.Add(newTank);
}

void ATankFactory::CheckTanks()
{
	// ������ ��� �������� �������� ���������� ���������� �� �����
	TArray<int> indexesDestroyedTanks{};

	for (int index = 0; index < activeTanks.Num(); ++index)
	{
		if (!(activeTanks[index]))
		{
			// ���� ���� ���������, �� ��������� ��� ������ � ������
			indexesDestroyedTanks.Add(index);
		}
	}

	// ���������� � ����� ������� ��� ��������� ������������� ������� �� �������
	for (int index = indexesDestroyedTanks.Num() - 1; index >= 0; --index)
	{
		// ������� ���������� ���� �� ������ �������� ������
		activeTanks.RemoveAt(index);
	}
}

