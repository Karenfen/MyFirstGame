#include "Cannon.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "Engine/Engine.h"
#include "Engine/EngineTypes.h"
#include "CollisionQueryParams.h"
#include "DamageTaker.h"
#include "GameStruct.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"
#include "GameFramework/ForceFeedbackEffect.h"


ACannon::ACannon()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* sceeneCpm = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = sceeneCpm;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cannon mesh"));
	Mesh->SetupAttachment(RootComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawnpoint"));
	ProjectileSpawnPoint->SetupAttachment(Mesh);

	ShootEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ShootEffect"));
	ShootEffect->SetupAttachment(ProjectileSpawnPoint);
	ShootEffect->SetAutoActivate(false);

	ShootAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioEffect"));
	ShootAudio->SetupAttachment(ProjectileSpawnPoint);
	ShootAudio->SetAutoActivate(false);

	ShootForceEffect = CreateDefaultSubobject<UForceFeedbackEffect>(TEXT("ShootForceEffect"));
}

ACannon::~ACannon()
{

}

void ACannon::Fire()
{
	if (!ReadyToFire)
	{
		return;
	}

	if (Ammo <= 0)
	{
		GEngine->AddOnScreenDebugMessage(10, 1, FColor::Red, "Ammo is empty");
		return;
	}

	ReadyToFire = false;

	switch (Type)
	{
	case ECannonType::FireProjectile:
		if (ProjectileShot())
			--Ammo;
		break;
	case ECannonType::FireTrace:
		TraceShot();
		break;
	case ECannonType::FireBurst:
		GetWorld()->GetTimerManager().SetTimer(BurstTimerHandle, this, &ACannon::Burst, 1.0f / BurstRate, true, 0.0f);
		break;
	}
		
	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this,	&ACannon::Reload, 1.0f / FireRate, false);
}

void ACannon::FireSpecial()
{
	if (!ReadyToFireSpec)
	{
		return;
	}

	if (Ammo <= 0)
	{
		GEngine->AddOnScreenDebugMessage(10, 1, FColor::Red, "Ammo is empty");
		return;
	}

	ReadyToFireSpec = false;

	switch (Type)
	{
	case ECannonType::FireProjectile:
		GetWorld()->GetTimerManager().SetTimer(BurstTimerHandle, this, &ACannon::Burst, 1.0f / BurstRate, true, 0.0f);
		break;
	case ECannonType::FireTrace:
		GetWorld()->GetTimerManager().SetTimer(BurstTimerHandle, this, &ACannon::TraceBurst, 1.0f / BurstRate, true, 0.0f);
		break;
	case ECannonType::FireBurst:
		GetWorld()->GetTimerManager().ClearTimer(BurstTimerHandle);
		currentShotInBurst = 10;
		GetWorld()->GetTimerManager().SetTimer(BurstTimerHandle, this, &ACannon::Burst, 1.0f / BurstRate, true, 0.0f);
		break;
	}

	GetWorld()->GetTimerManager().SetTimer(ReloadSpecTimerHandle, this, &ACannon::ReloadSpec, (1.0f / FireRate) * 3.0f, false);
}

bool ACannon::IsReadyToFire()
{	
	return ReadyToFire;
}

bool ACannon::IsReadyToFireSpec()
{
	return ReadyToFireSpec;
}

ECannonType ACannon::GetType()
{
	return Type;
}

bool ACannon::IsEmpty()
{
	return Ammo <= 0;
}

void ACannon::Resupply(uint8 numberRounds)
{
	Ammo += numberRounds;
	if (Ammo > maxAmmo)
		Ammo = maxAmmo;
}

void ACannon::BeginPlay()
{
	Super::BeginPlay();

	Reload();
	ReloadSpec();
	
}

void ACannon::Reload()
{
	ReadyToFire = true;
}

void ACannon::ReloadSpec()
{
	ReadyToFireSpec = true;
}

void ACannon::Burst()
{
	if (currentShotInBurst > 0)
	{
		if(ProjectileShot())
			--currentShotInBurst;
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(BurstTimerHandle);
		currentShotInBurst = ShotsInBurst;
		--Ammo;
	}
}



void ACannon::TraceBurst()
{
	if (currentShotInBurst > 0)
	{
		TraceShot();
		--currentShotInBurst;
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(BurstTimerHandle);
		currentShotInBurst = ShotsInBurst;
		--Ammo;
	}
}

bool ACannon::ProjectileShot()
{
	AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,
		ProjectileSpawnPoint->GetComponentLocation(),
		ProjectileSpawnPoint->GetComponentRotation());

	if (projectile)
	{
		projectile->SetOwner(this);
		projectile->Start();

		if(ShootEffect)
			ShootEffect->ActivateSystem();

		if(ShootAudio)
			ShootAudio->Play();

		FeedBack();

		return true;
	}

	return false;
}

void ACannon::TraceShot()
{
	FHitResult hitResult;
	FCollisionQueryParams traceParams =	FCollisionQueryParams(FName(TEXT("FireTrace")), true, this);
	traceParams.bTraceComplex = true;
	traceParams.bReturnPhysicalMaterial = false;
	FVector start = ProjectileSpawnPoint->GetComponentLocation();
	FVector end = ProjectileSpawnPoint->GetForwardVector() * FireRange + start;

	if (GetWorld()->LineTraceSingleByChannel(hitResult, start, end,	ECollisionChannel::ECC_Visibility, traceParams))
	{
		DrawDebugLine(GetWorld(), start, hitResult.Location, FColor::Red, false, 0.5f, 0, 5);

		IDamageTaker* enemy = Cast<IDamageTaker>(hitResult.GetActor());
		if (enemy)
		{ 
			FDamageData damageData;
			damageData.DamageValue = FireDamage;
			damageData.Instigator = GetOwner();
			damageData.DamageMaker = this;
			enemy->TakeDamage(damageData);
		}
	}
	else
	{
		DrawDebugLine(GetWorld(), start, end, FColor::Red, false, 0.5f, 0, 5);
	}

	if (ShootEffect)
		ShootEffect->ActivateSystem();

	if (ShootAudio)
		ShootAudio->Play();

	FeedBack();

	--Ammo;
}

void ACannon::FeedBack()
{
	if (GetOwner() != GetWorld()->GetFirstPlayerController()->GetPawn())
		return;

	if (ShootForceEffect)
	{
		FForceFeedbackParameters shootForceEffectParams;
		shootForceEffectParams.bLooping = false;
		shootForceEffectParams.Tag = "shootForceEffectParams";
		GetWorld()->GetFirstPlayerController()->ClientPlayForceFeedback(ShootForceEffect, shootForceEffectParams);
	}
}

