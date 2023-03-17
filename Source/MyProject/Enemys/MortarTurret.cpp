#include "MortarTurret.h"
#include "Components/ArrowComponent.h"
#include "../Cannons/MortarCannon.h"


void AMortarTurret::RotateTurretTo(FVector TargetPosition)
{
	// �� ������ ������ ������ �������� ����������
	if (!PlayerPawn || !CannonSetupPoint)
		return;

	Super::RotateTurretTo(TargetPosition);

	// ��������� ������� ������
	float distanceToPlayer = FVector::Distance(TargetPosition, turretLocation);		/* ������� ���������� �� ������ */
	float slopeFactor = TargetingRange / distanceToPlayer;		/* ������� ���������� ��� ������� */
	FRotator cannonRotation = CannonSetupPoint->GetRelativeRotation();		/* �������� ������� �������� �������� ������ */
	cannonRotation.Yaw = MinYawCannon - (RangeYawCannon / slopeFactor);		/* �� �������������� ������������� ������� �������� �������� ������� ���������������� ���������� �� ������� */
	CannonSetupPoint->SetRelativeRotation(cannonRotation);		/* � ������������� ���������� ������ ������ */
}

void AMortarTurret::BeginPlay()
{
	Super::BeginPlay();

	// ���������� ������������ ������������� ������ ������
	MinYawCannon =  0.0f - CannonSetupPoint->GetRelativeRotation().Yaw;

	// ������������� �������� ������� ������
	RangeYawCannon = MinYawCannon * 2.0f;

	// ������� ���� ������� ��� ���������� ��������
	turretLocation = GetActorLocation();
}

void AMortarTurret::Fire()
{
	AMortarCannon* MCannon = Cast<AMortarCannon>(Cannon);

	if (MCannon)
	{
		MCannon->SetAimingPoint(PlayerPawn->GetActorLocation());
	}

	Super::Fire();
}
