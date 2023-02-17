#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "IMachinery.h"
#include "DamageTaker.h"
#include "GameStruct.h"
#include "Components/PrimitiveComponent.h"
#include "Components/AudioComponent.h"
#include "Particles/ParticleSystemComponent.h"



AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* sceeneCpm = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = sceeneCpm;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
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
	GetWorld()->GetTimerManager().SetTimer(MovementTimerHandle, this, &AProjectile::Move, MoveRate, true, 0.0f);
}

void AProjectile::OnMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	AActor* owner = GetOwner();
	AActor* ownerByOwner = owner != nullptr ? owner->GetOwner() : nullptr;

	if (OtherActor != owner && OtherActor != ownerByOwner)
	{
		if (!MakeDamageTo(OtherActor))
			PushActor(OtherActor);

		// ��������� ����������� ������ � ������
		if (ExplodeAvailable)
		{
			// ������ ��� ����� ������������
			Explode();
		}

		Destroy();
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

bool AProjectile::MakeDamageTo(AActor* otherActor)
{
	IDamageTaker* damageTakerActor = Cast<IDamageTaker>(otherActor);

	if (!damageTakerActor)
		return false;

	FDamageData damageData;
	damageData.DamageValue = Damage;
	damageData.Instigator = GetOwner();
	damageData.DamageMaker = this;
	damageTakerActor->TakeDamage(damageData);

	return true;
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

