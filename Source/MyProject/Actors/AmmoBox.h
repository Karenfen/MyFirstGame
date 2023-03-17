#pragma once

#include "../Cannons/Cannon.h"
#include "CoreMinimal.h"
#include "../GameStruct.h"
#include "GameFramework/Actor.h"
#include "AmmoBox.generated.h"

UCLASS()
class MYPROJECT_API AAmmoBox : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Component")
		UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		TSubclassOf<ACannon> CannonClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		EAmmoBoxType Type = EAmmoBoxType::CannonBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		uint8 sizeAmmo = 10;

public:	
	AAmmoBox();

protected:
	UFUNCTION()
		void OnMeshOverLapBegin(UPrimitiveComponent* OverLappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweetResult);
};
