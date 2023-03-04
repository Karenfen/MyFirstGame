#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UPhysicsComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Moving params")
	float DistanceImterval = 10.0f;

public:	
	UPhysicsComponent();

	TArray<FVector> GenerateTrajectory(FVector StartPos, FVector EndPos);

};
