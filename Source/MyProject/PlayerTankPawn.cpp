// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerTankPawn.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <Components/AudioComponent.h>
#include "Cannon.h"
#include "IScorable.h"
#include "TankPlayerController.h"
#include "HealthComponent.h"
#include "Main_HUD_Widget.h"


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

void APlayerTankPawn::Fire()
{
	Super::Fire();

	if (IsValid(HUD))
	{
		HUD->SetCurGunAmmo(Cannon->GetAmmo(), Cannon->GetMaxAmmo());
	}
}

void APlayerTankPawn::Resupply(uint8 numberRounds)
{
	Super::Resupply(numberRounds);

	if (IsValid(HUD))
	{
		HUD->SetCurGunAmmo(Cannon->GetAmmo(), Cannon->GetMaxAmmo());
	}
}

void APlayerTankPawn::SwitchCannon()
{
	if (!IsValid(SecondCannon))
		return;

	ACannon* currentCannon = Cannon;
	Cannon = SecondCannon;
	SecondCannon = currentCannon;

	if (AudioChangeCannon)
		AudioChangeCannon->Play();

	if (Cannon)
	{
		Cannon->SetActorHiddenInGame(false);
		if (IsValid(HUD))
		{
			HUD->SetCurGunAmmo(Cannon->GetAmmo(), Cannon->GetMaxAmmo());
		}
	}
	if (SecondCannon)
	{
		SecondCannon->SetActorHiddenInGame(true);
		if (IsValid(HUD))
		{
			HUD->SetSecGunAmmo(SecondCannon->GetAmmo(), SecondCannon->GetMaxAmmo());
		}
	}
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
	{
		SecondCannon->SetActorHiddenInGame(true);
		if (IsValid(HUD))
		{
			HUD->SetSecGunAmmo(SecondCannon->GetAmmo(), SecondCannon->GetMaxAmmo());
		}
	}

	Super::SetupCannon(newCannonClass);

	if (IsValid(HUD))
	{
		HUD->SetCurGunAmmo(Cannon->GetAmmo(), Cannon->GetMaxAmmo());
	}
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

		if (IsValid(HUD))
		{
			HUD->SetCurGunAmmo(Cannon->GetAmmo(), Cannon->GetMaxAmmo());
		}
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

	if (IsValid(HUD))
	{
		HUD->SetScores(CurrentScores);
	}
}

void APlayerTankPawn::BeginPlay()
{
	Super::BeginPlay();

	TankController = Cast<ATankPlayerController>(GetController());

	HUD = CreateWidget<UMain_HUD_Widget>(TankController, HUD_widget);
	HUD->AddToViewport();

	if (!IsValid(HUD))
	{
		return;
	}

	if (IsValid(HealthComponent))
	{
		HUD->SetHealthStatus(HealthComponent->GetHealthState());
		HUD->SetCurrentHealthText(HealthComponent->GetCurrentHealth());
	}

	HUD->SetScores(CurrentScores);

	if (IsValid(Cannon))
	{
		HUD->SetCurGunAmmo(Cannon->GetAmmo(), Cannon->GetMaxAmmo());
	}
	if (IsValid(SecondCannon))
	{
		HUD->SetSecGunAmmo(SecondCannon->GetAmmo(), SecondCannon->GetMaxAmmo());
	}
}

void APlayerTankPawn::Die(AActor* killer)
{
	Super::Die(killer);
	//
	//
}

void APlayerTankPawn::DamageTaked(int DamageValue)
{
	Super::DamageTaked(DamageValue);

	HUD->SetHealthStatus(HealthComponent->GetHealthState());
	HUD->SetCurrentHealthText(HealthComponent->GetCurrentHealth());
}
