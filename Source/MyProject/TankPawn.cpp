#include "TankPawn.h"
#include "TankPlayerController.h"
#include "Cannon.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/ArrowComponent.h"
#include <Components/BoxComponent.h>
#include "HealthComponent.h"
#include "IScorable.h"
#include "Components/AudioComponent.h"
#include "Engine/TargetPoint.h"


ATankPawn::ATankPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank body"));
	RootComponent = BodyMesh;

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank turret"));
	TurretMesh->SetupAttachment(BodyMesh);

	HitCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Hit collider"));
	HitCollider->SetupAttachment(BodyMesh);

	CannonSetupPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Cannon setup point"));
	CannonSetupPoint->AttachToComponent(TurretMesh,	FAttachmentTransformRules::KeepRelativeTransform);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring arm"));
	SpringArm->SetupAttachment(BodyMesh);
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health	component"));
	HealthComponent->OnDie.AddUObject(this, &ATankPawn::Die);
	HealthComponent->OnDamaged.AddUObject(this, &ATankPawn::DamageTaked);

	AudioChangeCannon = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioChangeCannon"));
	AudioChangeCannon->SetupAttachment(TurretMesh);
	AudioChangeCannon->SetAutoActivate(false);

	AudioSetupCannon = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioSetupCannon"));
	AudioSetupCannon->SetupAttachment(TurretMesh);
	AudioSetupCannon->SetAutoActivate(false);

	AudioResupply = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioResupply"));
	AudioResupply->SetupAttachment(TurretMesh);
	AudioResupply->SetAutoActivate(false);
}

TSubclassOf<ACannon> ATankPawn::CurentCannonClass()
{
	return CannonClass;
}

void ATankPawn::Die(AActor* killer)
{
	if (killer)
		UE_LOG(LogTemp, Warning, TEXT("Tank was killed by %s"), *(killer->GetName()));

	ATankPawn* player = Cast<ATankPawn>(killer);
	if (player == GetWorld()->GetFirstPlayerController()->GetPawn() && player != nullptr)
		player->EnemyDestroyed(this);

	Destroy();
}

void ATankPawn::DamageTaked(float DamageValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Tank %s taked damage:%f Health:%f"), *GetName(),	DamageValue, HealthComponent->GetHealth());
}

void ATankPawn::BeginPlay()
{
	Super::BeginPlay();

	TankController = Cast<ATankPlayerController>( GetController());

	SetupCannon(CannonClass);

	CurrentScores = 0;

	
}

void ATankPawn::Resupply(uint8 numberRounds)
{
	if (Cannon)
	{
		Cannon->Resupply(numberRounds);
		if (AudioResupply)
			AudioResupply->Play();
	}
}

FVector ATankPawn::GetEyesPosition()
{
	return CannonSetupPoint->GetComponentLocation();
}

void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move(DeltaTime);
	Rotate(DeltaTime);

	//if (_TurretDirX == 0.0f && _TurretDirY == 0.0f)
		RotateTurret(DeltaTime);
	//else
		//RotateTurretTo(FVector(_TurretDirX, _TurretDirY, 0.0f) + GetActorLocation());
}

void ATankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATankPawn::MoveForward(float AxisValue)
{
	_targetForwardAxisValue = AxisValue;
}

void ATankPawn::MoveRight(float AxisValue)
{
	_targetRightdAxisValue = AxisValue;
}

void ATankPawn::RotateRight(float AxisValue)
{
	_targetRotateRightdAxisValue = AxisValue;
}

void ATankPawn::Fire()
{
	if (Cannon)
	{
		Cannon->Fire();
	}
}

void ATankPawn::FireSpecial()
{
	if (Cannon)
	{
		Cannon->FireSpecial();
	}
}

void ATankPawn::SwitchCannon()
{
	if (!SecondCannon)
		return;

	ACannon* currentCannon = Cannon;
	Cannon = SecondCannon;
	SecondCannon = currentCannon;

	if (Cannon)
		Cannon->SetActorHiddenInGame(false);
	if (SecondCannon)
		SecondCannon->SetActorHiddenInGame(true);

	if (AudioChangeCannon)
		AudioChangeCannon->Play();
}

void ATankPawn::TakeDamage(FDamageData DamageData)
{
	HealthComponent->TakeDamage(DamageData);
}

void ATankPawn::EnemyDestroyed(AActor* destroyedObject)
{
	IIScorable* enemy = Cast<IIScorable>(destroyedObject);
	if (!enemy)
		return;

	CurrentScores += enemy->GetScores();

	if (CurrentScores > MaxScores)
		CurrentScores = MaxScores;

	UE_LOG(LogTemp, Warning, TEXT("Scores: %d"), CurrentScores);
}

TArray<FVector> ATankPawn::GetPatrollingPoints()
{
	TArray<FVector> points;

	for (ATargetPoint* point : PatrollingPoints)
	{
		points.Add(point->GetActorLocation());
	}

	return points;
}

void ATankPawn::SetPatrollingPoints(TArray<ATargetPoint*> NewPatrollingPoints)
{
	PatrollingPoints = NewPatrollingPoints;
}

void ATankPawn::Move(float DeltaTime)
{
	if (_targetForwardAxisValue == 0.0f)
		return;

	if (RootComponent->IsSimulatingPhysics())
	{
		UPrimitiveComponent* mesh = Cast<UPrimitiveComponent>(RootComponent);
		if (mesh)
		{
			mesh->AddForce(GetActorForwardVector() * EnginePower * DeltaTime * _targetForwardAxisValue, NAME_None, true);
			return;
		}
	}

	FVector currentLocation = GetActorLocation();
	FVector forwardVector = GetActorForwardVector();
	FVector rightVector = GetActorRightVector();
	FVector movePosition = currentLocation + ((forwardVector * _targetForwardAxisValue + rightVector * _targetRightdAxisValue) * MoveSpeed * DeltaTime);
	SetActorLocation(movePosition, true);
}

void ATankPawn::Rotate(float DeltaTime)
{
	float yawRotation = RotationSpeed * _targetRotateRightdAxisValue * DeltaTime;
	FRotator currentRotation = GetActorRotation();

	currentRotation.Yaw += yawRotation;
	SetActorRotation(currentRotation);
}

void ATankPawn::RotateTurret(float DeltaTime)
{
	if (TankController)
		RotateTurretTo(TankController->GetMousePosition());
}

void ATankPawn::Destroyed()
{
	if (Cannon)
		Cannon->Destroy();
}

void ATankPawn::SetupCannon(TSubclassOf<ACannon> newCannonClass)
{
	if (AudioSetupCannon)
		AudioSetupCannon->Play();

	if (!newCannonClass)
	{
		return;
	}

	if (Cannon)
	{
		if (SecondCannon)
			Cannon->Destroy();
		else
			SecondCannon = Cannon;
	}

	FActorSpawnParameters params;
	params.Instigator = this;
	params.Owner = this;

	Cannon = GetWorld()->SpawnActor<ACannon>(newCannonClass, params);
	Cannon->AttachToComponent(CannonSetupPoint,	FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	if (SecondCannon)
		SecondCannon->SetActorHiddenInGame(true);
}

FVector ATankPawn::GetTurretForwardVector()
{
	return TurretMesh->GetForwardVector();
}

void ATankPawn::RotateTurretTo(FVector TargetPosition)
{
	FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetPosition);
	FRotator turretRotation = TurretMesh->GetComponentRotation();
	targetRotation.Pitch = turretRotation.Pitch;
	targetRotation.Roll = turretRotation.Roll;
	FRotator newTurretRotation = FMath::Lerp(turretRotation, targetRotation, TurretRotationInterpolationKey);
	TurretMesh->SetWorldRotation(newTurretRotation);
}

void ATankPawn::SetTurretDirX(float AxisValue)
{
	_TurretDirX = AxisValue;
}

void ATankPawn::SetTurretDirY(float AxisValue)
{
	_TurretDirY = AxisValue;
}