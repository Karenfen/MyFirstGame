// Fill out your copyright notice in the Description page of Project Settings.


#include "MachineryActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "HealthComponent.h"
#include <Components/AudioComponent.h>
#include <Kismet/KismetMathLibrary.h>
#include "Cannon.h"


// Sets default values
AMachineryActor::AMachineryActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	RootComponent = BodyMesh;

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret"));
	TurretMesh->AttachToComponent(BodyMesh, FAttachmentTransformRules::KeepRelativeTransform, "ADD_Parts_Here_Socket");

	CannonSetupPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Cannon setup point"));
	CannonSetupPoint->AttachToComponent(TurretMesh, FAttachmentTransformRules::KeepRelativeTransform, "Cannon_Setup_Socket");

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health	component"));
	HealthComponent->OnDie.AddUObject(this, &AMachineryActor::Die);
	HealthComponent->OnDamaged.AddUObject(this, &AMachineryActor::DamageTaked);

	AudioResupply = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioResupply"));
	AudioResupply->SetupAttachment(TurretMesh);
	AudioResupply->SetAutoActivate(false);
}

// Called when the game starts or when spawned
void AMachineryActor::BeginPlay()
{
	Super::BeginPlay();

	SetupCannon(CannonClass);
}

void AMachineryActor::Fire()
{
	if (IsValid(Cannon))
	{
		Cannon->Fire();
	}
}

void AMachineryActor::Resupply(uint8 numberRounds)
{
	if (IsValid(Cannon))
	{
		if (AudioResupply)
			AudioResupply->Play();

		Cannon->Resupply(numberRounds);
	}
}

void AMachineryActor::SetupCannon(TSubclassOf<ACannon> newCannonClass)
{
	FActorSpawnParameters params;
	params.Instigator = this;
	params.Owner = this;

	Cannon = GetWorld()->SpawnActor<ACannon>(newCannonClass, params);
	Cannon->AttachToComponent(CannonSetupPoint, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void AMachineryActor::TakeDamage_(FDamageData DamageData)
{
	HealthComponent->TakeDamage(DamageData);
}

void AMachineryActor::Die(AActor* killer)
{
	Destroy();
}

void AMachineryActor::Destroyed()
{
	if (IsValid(Cannon))
		Cannon->Destroy();
}

void AMachineryActor::DamageTaked(float DamageValue)
{
	UE_LOG(LogTemp, Warning, TEXT("%s taked damage:%f Health:%f"), *GetName(), DamageValue, HealthComponent->GetHealth());
}

void AMachineryActor::RotateTurretTo(FVector TargetPosition)
{
	if (!IsValid(TurretMesh))
	{
		return;
	}

	FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetPosition);
	FRotator turretRotation = TurretMesh->GetComponentRotation();
	targetRotation.Pitch = turretRotation.Pitch;
	targetRotation.Roll = turretRotation.Roll;
	TurretMesh->SetWorldRotation(FMath::Lerp(turretRotation, targetRotation, TurretRotationInterpolationKey));
}

FVector AMachineryActor::GetEyesPosition()
{
	return CannonSetupPoint->GetComponentLocation();
}