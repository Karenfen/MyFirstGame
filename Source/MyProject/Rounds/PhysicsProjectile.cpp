#include "PhysicsProjectile.h"
#include "DrawDebugHelpers.h"
#include "../Components/PhysicsComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Particles/ParticleSystemComponent.h"
#include "../Interfaces/DamageTaker.h"
#include "../GameStruct.h"
#include "CollisionShape.h"
#include "CollisionQueryParams.h"
#include "Engine/EngineTypes.h"


APhysicsProjectile::APhysicsProjectile()
{
	PhysicsComponent = CreateDefaultSubobject<UPhysicsComponent>(TEXT("PhysicsComponent"));

	TrailEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Trail effect"));
	TrailEffect->SetupAttachment(RootComponent);
	TrailEffect->SetAutoActivate(false);
}

APhysicsProjectile::~APhysicsProjectile()
{

}

void APhysicsProjectile::Start()
{
	Super::Start();

	CurrentTrajectory = PhysicsComponent->GenerateTrajectory(GetActorLocation(), DestinationPosition);
	
	if (ShowTrajectory)
	{
		for (const FVector& position : CurrentTrajectory)
		{
			DrawDebugSphere(GetWorld(), position, 5.0f, 8, FColor::Purple, false, 5.0f, 0,	2.0f);
		}
	}

	TragectoryPointIndex = 0;

	if (TrailEffect)
		TrailEffect->ActivateSystem();

}

void APhysicsProjectile::SetDestinationPoint(const FVector& endPos)
{
	DestinationPosition = endPos;
}

void APhysicsProjectile::Move()
{
	if (TragectoryPointIndex >= CurrentTrajectory.Num())
	{
		return;
	}

	FVector currentMoveVector = CurrentTrajectory[TragectoryPointIndex] - GetActorLocation();
	currentMoveVector.Normalize();

	FVector newLocation = GetActorLocation() + currentMoveVector * MoveSpeed * MoveRate;
	SetActorLocation(newLocation);

	if (FVector::Distance(newLocation, CurrentTrajectory[TragectoryPointIndex]) <= MoveAccurency)
	{
		TragectoryPointIndex++;

		if (TragectoryPointIndex >= CurrentTrajectory.Num())
		{
			// проверяем доступность взрыва в классе
			if (ExplodeAvailable)
				Explode();
			
			Die();
		}
		else
		{
			FRotator newRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), CurrentTrajectory[TragectoryPointIndex]);
			SetActorRotation(newRotation);
		}
	}
}