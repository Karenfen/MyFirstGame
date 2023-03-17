#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PoolProjectiles.generated.h"

class ABaseAmmoClass;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UPoolProjectiles : public UActorComponent
{
	GENERATED_BODY()

protected:
	// для установки размера пулла через блупринты
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Size")
	int PoolSize = 2;

	// для установки класса проджектайлов через блупринты
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Type")
	TSubclassOf<ABaseAmmoClass> ProjectileClass;

	// нулевая координата для проджектайлов
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Zero point")
	FVector ZeroLocation;

	// массив проджектайлов
	TArray<ABaseAmmoClass*> Pool;

public:	
	UPoolProjectiles();
	~UPoolProjectiles();

	// получение проджуктайла
	ABaseAmmoClass* GetProjectile(FVector toPosition);

protected:
	virtual void BeginPlay() override;
	ABaseAmmoClass* CreateProjectile(); // метод создания обьекта
	
};
