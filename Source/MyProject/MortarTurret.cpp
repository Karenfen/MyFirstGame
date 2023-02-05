#include "MortarTurret.h"
#include "Components/ArrowComponent.h"


void AMortarTurret::RotateTurret(float DeltaTime)
{
	Super::RotateTurret(DeltaTime);

	// �� ������ ������ ������ �������� ����������
	if (!PlayerPawn || !CannonSetupPoint)
		return;

	// ��������� ������� ������
	float distanceToPlayer = FVector::Distance(PlayerPawn->GetActorLocation(), turretLocation);		/* ������� ���������� �� ������ */
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
