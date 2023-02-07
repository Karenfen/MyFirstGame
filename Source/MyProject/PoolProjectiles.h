#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PoolProjectiles.generated.h"

class AProjectileForPool;


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
	TSubclassOf<AProjectileForPool> ProjectileClass;

	// нулевая координата для проджектайлов
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Zero point")
	FVector ZeroLocation;

	// массив проджектайлов
	TArray<AProjectileForPool*> Pool;

public:	
	UPoolProjectiles();
	~UPoolProjectiles();

	// получение проджуктайла
	AProjectileForPool* GetProjectile(FVector toPosition);

protected:
	virtual void BeginPlay() override;
	AProjectileForPool* CreateProjectile(); // метод создания обьекта
	
};
