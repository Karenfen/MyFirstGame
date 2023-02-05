#include "MortarTurret.h"
#include "Components/ArrowComponent.h"


void AMortarTurret::RotateTurret(float DeltaTime)
{
	Super::RotateTurret(DeltaTime);

	// на всякий случай делаем проверку указателей
	if (!PlayerPawn || !CannonSetupPoint)
		return;

	// изменение наклона орудия
	float distanceToPlayer = FVector::Distance(PlayerPawn->GetActorLocation(), turretLocation);		/* находим расстояние до игрока */
	float slopeFactor = TargetingRange / distanceToPlayer;		/* находим коэфициент для наклона */
	FRotator cannonRotation = CannonSetupPoint->GetRelativeRotation();		/* получаем текущее значение поворота орудия */
	cannonRotation.Yaw = MinYawCannon - (RangeYawCannon / slopeFactor);		/* от отрицательного максимального наклона отнимаем диапазон наклона пропорциональный расстоянию до игррока */
	CannonSetupPoint->SetRelativeRotation(cannonRotation);		/* и устанавливаем полученный наклон орудию */
}

void AMortarTurret::BeginPlay()
{
	Super::BeginPlay();

	// определяем максимальный отрицательный наклон орудия
	MinYawCannon =  0.0f - CannonSetupPoint->GetRelativeRotation().Yaw;

	// устанавливаем диапазон наклона орудия
	RangeYawCannon = MinYawCannon * 2.0f;

	// находим нашу позицию для дальнейших расчетов
	turretLocation = GetActorLocation();
}
