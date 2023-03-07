// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerTankPawn.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <Components/AudioComponent.h>
#include "Cannon.h"
#include "IScorable.h"
#include "TankPlayerController.h"
#include "HealthComponent.h"


APlayerTankPawn::APlayerTankPawn()
{
	SpringArm = APawn::CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring arm"));
	SpringArm->SetupAttachment(BodyMesh);
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;

	Camera = APawn::CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	AudioChangeCannon = APawn::CreateDefaultSubobject<UAudioComponent>(TEXT("AudioChangeCannon"));
	AudioChangeCannon->SetupAttachment(TurretMesh);
	AudioChangeCannon->SetAutoActivate(false);
}

void APlayerTankPawn::SwitchCannon()
{
	if (!SecondCannon)
		return;

	ACannon* currentCannon = Cannon;
	Cannon = SecondCannon;
	SecondCannon = currentCannon;

	if (AudioChangeCannon)
		AudioChangeCannon->Play();

	if (Cannon)
		Cannon->SetActorHiddenInGame(false);
	if (SecondCannon)
		SecondCannon->SetActorHiddenInGame(true);

}

void APlayerTankPawn::SetupCannon(TSubclassOf<ACannon> newCannonClass)
{
	if (!newCannonClass)
	{
		return;
	}

	if (Cannon)
	{
		if (SecondCannon)
		{
			Cannon->Destroy();
		}
		else
		{
			SecondCannon = Cannon;
		}
	}

	if (SecondCannon)
		SecondCannon->SetActorHiddenInGame(true);

	Super::SetupCannon(newCannonClass);
}

FPlayerStatus APlayerTankPawn::GetStatus() const
{
	FPlayerStatus status;

	if (IsValid(HealthComponent))
	{
		status.CurrentHealth = HealthComponent->GetCurrentHealth();
		status.MaxHealth = HealthComponent->GetMaxHealth();
	}
	if (IsValid(Cannon))
	{
		status.FirstCannon = Cannon->GetName();
		status.FCAmmo = Cannon->GetAmmo();
		status.FCMaxAmmo = Cannon->GetMaxAmmo();
	}
	if (IsValid(SecondCannon))
	{
		status.SecondCannon = SecondCannon->GetName();
		status.SCAmmo = SecondCannon->GetAmmo();
		status.SCMaxAmmo = SecondCannon->GetMaxAmmo();
	}
	status.Scores = CurrentScores;

	return status;
}

void APlayerTankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (_TurretDirX == 0.0f && _TurretDirY == 0.0f)
	if (TankController)
		RotateTurretTo(TankController->GetMousePosition());
	//else
		//RotateTurretTo(FVector(_TurretDirX, _TurretDirY, 0.0f) + GetActorLocation());
}

void APlayerTankPawn::FireSpecial()
{
	if (IsValid(Cannon))
	{
		Cannon->FireSpecial();
	}
}

void APlayerTankPawn::EnemyDestroyed(AActor* destroyedObject)
{
	IIScorable* enemy = Cast<IIScorable>(destroyedObject);
	if (!enemy)
		return;

	CurrentScores += enemy->GetScores();

	if (CurrentScores > MaxScores)
		CurrentScores = MaxScores;

	UE_LOG(LogTemp, Warning, TEXT("Scores: %d"), CurrentScores);
}

void APlayerTankPawn::BeginPlay()
{
	Super::BeginPlay();

	TankController = Cast<ATankPlayerController>(GetController());
}

void APlayerTankPawn::Die(AActor* killer)
{
	Super::Die(killer);
	//
	//
}
