// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerTankPawn.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <Components/AudioComponent.h>
#include "../Cannons/Cannon.h"
#include "../Interfaces/IScorable.h"
#include "TankPlayerController.h"
#include "../Components/HealthComponent.h"
#include "../HUD/Main_HUD_Widget.h"


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

	UpdateCCAmmoHUD();
}

void APlayerTankPawn::Resupply(uint8 numberRounds)
{
	Super::Resupply(numberRounds);

	UpdateCCAmmoHUD();
}

void APlayerTankPawn::SwitchCannon()
{
	if (!IsValid(SecondCannon))
		return;

	ACannon* currentCannon = Cannon;
	Cannon = SecondCannon;
	SecondCannon = currentCannon;

	TSubclassOf<ACannon> currentCannonClass = CannonClass;
	CannonClass = SecondCannonClass;
	SecondCannonClass = currentCannonClass;

	if (AudioChangeCannon)
		AudioChangeCannon->Play();

	if (Cannon)
	{
		Cannon->SetActorHiddenInGame(false);
		UpdateCCAmmoHUD();
		UpdateCCIconHUD();
	}
	if (SecondCannon)
	{
		SecondCannon->SetActorHiddenInGame(true);
		UpdateSCAmmoHUD();
		UpdateSCIconHUD();
	}
}

void APlayerTankPawn::SetupCannon(TSubclassOf<ACannon> newCannonClass)
{
	if (!newCannonClass)
	{
		return;
	}

	if (IsValid(Cannon))
	{
		if(CannonClass == newCannonClass)
		{
			Resupply();
			return;
		}

		if (IsValid(SecondCannon))
		{
			if (SecondCannonClass == newCannonClass)
			{
				if (IsValid(AudioResupply))
					AudioResupply->Play();

				SecondCannon->Resupply();
				UpdateSCAmmoHUD();

				return;
			}

			Cannon->Destroy();
		}
		else
		{
			SecondCannon = Cannon;
			SecondCannonClass = CannonClass;
			SecondCannon->SetActorHiddenInGame(true);
			UpdateSCAmmoHUD();
			UpdateSCIconHUD();
		}
	}

	Super::SetupCannon(newCannonClass);

	UpdateCCAmmoHUD();
	UpdateCCIconHUD();
}

void APlayerTankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (_TurretDirX == 0.0f && _TurretDirY == 0.0f)
	if (TankController)
		RotateTurretTo(TankController->GetTurretTarget());
	//else
		//RotateTurretTo(FVector(_TurretDirX, _TurretDirY, 0.0f) + GetActorLocation());
}

void APlayerTankPawn::FireSpecial()
{
	if (IsValid(Cannon))
	{
		Cannon->FireSpecial();
		UpdateCCAmmoHUD();
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

	UpdateScoresHUD();
}

void APlayerTankPawn::BeginPlay()
{
	Super::BeginPlay();

	SetupCannon(SecondCannonClass);

	TankController = Cast<ATankPlayerController>(GetController());

	HUD = CreateWidget<UMain_HUD_Widget>(TankController, HUD_widget);
	HUD->AddToViewport();

	UpdateHUD();
}

void APlayerTankPawn::Die(AActor* killer)
{
	Super::Die(killer);

	if (IsValid(SecondCannon))
	{
		SecondCannon->Destroy();
	}
}

void APlayerTankPawn::DamageTaked(int DamageValue)
{
	Super::DamageTaked(DamageValue);

	UpdateHealteHUD();
}

void APlayerTankPawn::UpdateHUD()
{
	UpdateHealteHUD();
	UpdateScoresHUD();
	UpdateCCAmmoHUD();
	UpdateSCAmmoHUD();
	UpdateCCIconHUD();
	UpdateSCIconHUD();
}

void APlayerTankPawn::UpdateHealteHUD()
{
	if (IsValid(HUD) && IsValid(HealthComponent))
	{
		HUD->SetHealthStatus(HealthComponent->GetHealthState());
		HUD->SetCurrentHealthText(HealthComponent->GetCurrentHealth());
	}
}

void APlayerTankPawn::UpdateScoresHUD()
{
	if (IsValid(HUD))
	{
		HUD->SetScores(CurrentScores);
	}
}

void APlayerTankPawn::UpdateCCAmmoHUD()
{
	if (IsValid(Cannon) && IsValid(HUD))
	{
		HUD->SetCurGunAmmo(Cannon->GetAmmo(), Cannon->GetMaxAmmo());
	}
}

void APlayerTankPawn::UpdateSCAmmoHUD()
{
	if (IsValid(SecondCannon) && IsValid(HUD))
	{
		HUD->SetSecGunAmmo(SecondCannon->GetAmmo(), SecondCannon->GetMaxAmmo());
	}
}

void APlayerTankPawn::UpdateCCIconHUD()
{
	if (IsValid(HUD) && IsValid(Cannon))
	{
		HUD->SetCurGunIcon(Cannon->GetIconBrush());
	}
}

void APlayerTankPawn::UpdateSCIconHUD()
{
	if (IsValid(HUD) && IsValid(SecondCannon))
	{
		HUD->SetSecGunIcon(SecondCannon->GetIconBrush());
	}
}
