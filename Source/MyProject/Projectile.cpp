#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "IMachinery.h"
#include "DamageTaker.h"
#include "GameStruct.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	USceneComponent* sceeneCpm = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = sceeneCpm;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnMeshOverlapBegin);
}

AProjectile::~AProjectile()
{

}

void AProjectile::Start()
{
	GetWorld()->GetTimerManager().SetTimer(MovementTimerHandle, this, &AProjectile::Move, MoveRate, true, 0.0f);
}

void AProjectile::OnMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	AActor* owner = GetOwner();
	AActor* ownerByOwner = owner != nullptr ? owner->GetOwner() : nullptr;

	if (OtherActor != owner && OtherActor != ownerByOwner)
	{
		IDamageTaker* damageTakerActor = Cast<IDamageTaker>(OtherActor);
		if (damageTakerActor)
		{
			FDamageData damageData;
			damageData.DamageValue = Damage;
			damageData.Instigator = ownerByOwner;
			damageData.DamageMaker = this;
			damageTakerActor->TakeDamage(damageData);
		}
		//������ �������� ����� �� ������� ��������������
		//UFoliageType_Actor* foliage = Cast<UFoliageType_Actor>(OtherActor);
		//if(!foliage)
		//	OtherActor->Destroy();

		Destroy();
	}

}

void AProjectile::Move()
{
	FVector nextPosition = GetActorLocation() + GetActorForwardVector() * MoveSpeed	* MoveRate;
	SetActorLocation(nextPosition);
}