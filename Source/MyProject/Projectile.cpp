#include "Projectile.h"
#include "TimerManager.h"
#include "DamageTaker.h"
#include "GameStruct.h"
#include "Components/PrimitiveComponent.h"
#include "Components/AudioComponent.h"
#include "Particles/ParticleSystemComponent.h"



AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnMeshOverlapBegin);

	// �������������� ���������� ������ ������
	ExplodeEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Explode effect"));
	ExplodeEffect->SetupAttachment(RootComponent);
	ExplodeEffect->SetAutoActivate(false);

	// �������������� ����� ������ ������
	ExplodeAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("Explode Sound"));
	ExplodeAudio->SetupAttachment(RootComponent);
	ExplodeAudio->SetAutoActivate(false);
}

AProjectile::~AProjectile()
{

}

void AProjectile::Start()
{
	Super::Start();

	GetWorld()->GetTimerManager().SetTimer(MovementTimerHandle, this, &AProjectile::Move, MoveRate, true, 0.0f);

	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
}

void AProjectile::OnMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	AActor* owner = GetOwner();
	AActor* ownerByOwner = owner != nullptr ? owner->GetOwner() : nullptr;

	if (OtherActor != owner && OtherActor != ownerByOwner)
	{
		// stop timer to destroy
		GetWorld()->GetTimerManager().ClearTimer(DestroyTimerHandle);

		if (!MakeDamageTo(OtherActor))
			PushActor(OtherActor);

		// ��������� ����������� ������ � ������
		if (ExplodeAvailable)
		{
			// ������ ��� ����� ������������
			Explode();
		}

		Die();
	}

}

void AProjectile::Move()
{
	FVector nextPosition = GetActorLocation() + GetActorForwardVector() * MoveSpeed	* MoveRate;
	SetActorLocation(nextPosition);
}

void AProjectile::Explode()
{
	// ������������� ����
	if (ExplodeAudio)
		ExplodeAudio->Play();

	// ��������� ���������� ������
	if (ExplodeEffect)
		ExplodeEffect->ActivateSystem();

	FVector startPos = GetActorLocation();
	FVector endPos = startPos + FVector(0.1f);
	FCollisionShape Shape = FCollisionShape::MakeSphere(ExplodeRadius);

	FCollisionQueryParams params = FCollisionQueryParams::DefaultQueryParam;
	params.AddIgnoredActor(this);
	params.bTraceComplex = true;
	params.TraceTag = "Explode Trace";

	TArray<FHitResult> AttackHit;
	FQuat Rotation = FQuat::Identity;

	bool sweepResult = GetWorld()->SweepMultiByChannel
	(
		AttackHit,
		startPos,
		endPos,
		Rotation,
		ECollisionChannel::ECC_Visibility,
		Shape,
		params
	);

	GetWorld()->DebugDrawTraceTag = "Explode Trace";

	if (sweepResult)
	{
		for (FHitResult hitResult : AttackHit)
		{
			AActor* otherActor = hitResult.GetActor();

			if (!otherActor)
				continue;

			if(!MakeDamageTo(otherActor))
				PushActor(otherActor);
		}
	}
}

bool AProjectile::PushActor(AActor* otherActor)
{
	if (!otherActor)
		return false;

	UPrimitiveComponent* mesh = Cast<UPrimitiveComponent>(otherActor->GetRootComponent());

	if (!mesh)
		return false;

	if (!mesh->IsSimulatingPhysics())
		return false;

	FVector forceVector = otherActor->GetActorLocation() - GetActorLocation();
	forceVector.Normalize();

	mesh->AddImpulse(forceVector * PushForce, NAME_None, true);

	return true;
}

void AProjectile::Die()
{
	if (ExplodeAvailable)
	{	// останавливаем таймер движения
		GetWorld()->GetTimerManager().ClearTimer(MovementTimerHandle);
		// скрываем
		Mesh->SetHiddenInGame(true);
		// выключаем коллизию
		SetActorEnableCollision(false);
		// to destroy after explosion
		GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, this, &AProjectile::Destroy_, TimeToDestroyAfterHit, false);
	}
	else
	{
		Destroy_();
	}
}

bool AProjectile::MakeDamageTo(AActor* otherActor)
{
	IDamageTaker* damageTakerActor = Cast<IDamageTaker>(otherActor);

	if (!damageTakerActor)
		return false;

	FDamageData damageData;
	damageData.DamageValue = Damage;
	damageData.Instigator = GetOwner();
	damageData.DamageMaker = this;
	damageTakerActor->TakeDamage_(damageData);

	return true;
}

void AProjectile::Destroy_()
{
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
		Destroy();
	}
}

