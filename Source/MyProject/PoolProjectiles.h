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
	// ��� ��������� ������� ����� ����� ���������
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Size")
	int PoolSize = 2;

	// ��� ��������� ������ ������������� ����� ���������
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Type")
	TSubclassOf<AProjectileForPool> ProjectileClass;

	// ������� ���������� ��� �������������
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Zero point")
	FVector ZeroLocation;

	// ������ �������������
	TArray<AProjectileForPool*> Pool;

public:	
	UPoolProjectiles();
	~UPoolProjectiles();

	// ��������� ������������
	AProjectileForPool* GetProjectile(FVector toPosition);

protected:
	virtual void BeginPlay() override;
	AProjectileForPool* CreateProjectile(); // ����� �������� �������
	
};
