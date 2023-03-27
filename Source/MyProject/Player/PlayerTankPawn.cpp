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
#include "../SavePlayerState.h"
#include <Kismet/KismetMathLibrary.h>
#include "Kismet/GameplayStatics.h"
#include "Components/ArrowComponent.h"



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

void APlayerTankPawn::AddCannon(TSubclassOf<ACannon> newCannonClass)
{
	if (!newCannonClass)
	{
		return;
	}

	if (!IsValid(Cannon))
	{
		SetupCannon(newCannonClass);
		return;
	}

	if (!IsValid(SecondCannon))
	{
		SetupSecondCannon(newCannonClass);
		return;
	}

	if (CannonClass == newCannonClass)
	{
		Resupply();
		return;
	}

	if (SecondCannonClass == newCannonClass)
	{
		if (IsValid(AudioResupply))
		{
			AudioResupply->Play();
		}

		SecondCannon->Resupply();
		UpdateSCAmmoHUD();

		return;
	}

	SetupCannon(newCannonClass);
}

void APlayerTankPawn::SetupCannon(TSubclassOf<ACannon> newCannonClass)
{
	if (!newCannonClass)
	{
		return;
	}

	Super::SetupCannon(newCannonClass);

	UpdateCCAmmoHUD();
	UpdateCCIconHUD();
}

void APlayerTankPawn::SetupSecondCannon(TSubclassOf<ACannon> newCannonClass)
{
	if (newCannonClass)
	{
		if (IsValid(SecondCannon))
		{
			SecondCannon->Destroy();
		}

		FActorSpawnParameters params;
		params.Instigator = this;
		params.Owner = this;

		SecondCannon = GetWorld()->SpawnActor<ACannon>(newCannonClass, params);

		if(IsValid(SecondCannon))
		{
			SecondCannon->AttachToComponent(CannonSetupPoint, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			SecondCannonClass = newCannonClass;

			if (IsValid(AudioSetupCannon))
			{
				AudioSetupCannon->Play();
			}

			UpdateSCAmmoHUD();
			UpdateSCIconHUD();
		}
	}
}

void APlayerTankPawn::SetStateAfterInit()
{
	if (state.CurrentHealth > 0 && IsValid(HealthComponent))
	{
		HealthComponent->SetCurrentHealth(state.CurrentHealth);
	}

	if (state.FCAmmo >= 0 && IsValid(Cannon))
	{
		Cannon->SetAmmo(state.FCAmmo);
	}

	if (state.SCAmmo >= 0 && IsValid(SecondCannon))
	{
		SecondCannon->SetAmmo(state.SCAmmo);
	}

	if (state.Scores >= 0)
	{
		CurrentScores = state.Scores;
	}
}

void APlayerTankPawn::SetStateBeforeInit()
{
	if (state.FirstCannon)
	{
		CannonClass = state.FirstCannon;
	}

	if (state.SecondCannon)
	{
		SecondCannonClass = state.SecondCannon;
	}
}

void APlayerTankPawn::UpdateState()
{
	state.FirstCannon = CannonClass;
	state.SecondCannon = SecondCannonClass;
	state.Scores = CurrentScores;

	if (IsValid(Cannon))
	{
		state.FCAmmo = Cannon->GetAmmo();
	}
	if (IsValid(HealthComponent))
	{
		state.CurrentHealth = HealthComponent->GetHealth();
	}
	if (IsValid(SecondCannon))
	{
		state.SCAmmo = SecondCannon->GetAmmo();
	}
}

FPlayerTankState APlayerTankPawn::GetState()
{
	UpdateState();

	return state;
}

void APlayerTankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsValid(TankController))
	{
		RotateTurretTo(TankController->GetTurretTarget());
	}

	if (GetActorLocation().Z <= deathHeight)
	{
		Die(this);
	}
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
	USavePlayerState* savePlayerInstance = Cast<USavePlayerState>(UGameplayStatics::CreateSaveGameObject(USavePlayerState::StaticClass()));
	savePlayerInstance = Cast<USavePlayerState>(UGameplayStatics::LoadGameFromSlot("Player state", 0));

	if (IsValid(savePlayerInstance))
	{
		state = savePlayerInstance->GetPlayerState();
	}

	SetStateBeforeInit();

	Super::BeginPlay();

	TankController = Cast<ATankPlayerController>(GetController());

	HUD = CreateWidget<UMain_HUD_Widget>(TankController, HUD_widget);
	HUD->AddToViewport();

	SetupSecondCannon(SecondCannonClass);
	SetStateAfterInit();
	UpdateHUD();
}

void APlayerTankPawn::Die(AActor* killer)
{
	Super::Die(killer);

	if (IsValid(SecondCannon))
	{
		SecondCannon->Destroy();
	}

	if (OnDie.IsBound())
	{
		OnDie.Broadcast();
	}
}

void APlayerTankPawn::DamageTaked(int DamageValue)
{
	Super::DamageTaked(DamageValue);

	UpdateHealteHUD();
}

void APlayerTankPawn::Rotate(float DeltaTime)
{
	
	if (IsValid(TankController))
	{
		FVector target = TankController->GetTankTargetRotation();
		if (target == FVector::ZeroVector)
		{
			Super::Rotate(DeltaTime);
		}
		else
		{
			RotateBodyTo(target);
		}
	}
}

void APlayerTankPawn::RotateBodyTo(const FVector& target)
{
	FRotator newRotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), target);
	FRotator bodyRotator = GetActorRotation();
	float angleTurretYawRelativeBody = UKismetMathLibrary::DegreesToRadians(newRotator.Yaw - bodyRotator.Yaw);

	newRotator.Pitch = bodyRotator.Pitch * UKismetMathLibrary::Cos(angleTurretYawRelativeBody) - bodyRotator.Roll * UKismetMathLibrary::Sin(angleTurretYawRelativeBody);
	newRotator.Roll = bodyRotator.Roll * UKismetMathLibrary::Cos(angleTurretYawRelativeBody) + bodyRotator.Pitch * UKismetMathLibrary::Sin(angleTurretYawRelativeBody);
	
	BodyMesh->SetWorldRotation(FMath::Lerp(GetActorRotation(), newRotator, TankRotationInterpolationKey));
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
