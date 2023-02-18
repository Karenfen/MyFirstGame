#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class MYPROJECT_API AProjectile : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
	float MoveSpeed = 500;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
	float MoveRate = 0.005f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
	float Damage = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
	float PushForce = 1000;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage|Explode")
	float ExplodeRadius = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage|Explode")
	bool ExplodeAvailable = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Live")
	float TimeToDestroyAfterHit = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Live")
	float TimeToLive = 5.0f;

	// ��������� ���������� ������ ������
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Effects")
	class UParticleSystemComponent* ExplodeEffect;

	// ��������� ����� ������ ������
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Effects")
	class UAudioComponent* ExplodeAudio;

	FTimerHandle MovementTimerHandle;
	FTimerHandle DestroyTimerHandle;
	
public:	
	AProjectile();
	virtual ~AProjectile();
	virtual void Start();

protected:
	UFUNCTION()
	virtual void OnMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor*
			OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool
			bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void Move();

	UFUNCTION()
	virtual void Explode();

	// ����� �� ��������� ����� ��� ���������
	UFUNCTION()
	bool MakeDamageTo(AActor* otherActor);

	// ����� �� ������������ �������
	UFUNCTION()
	bool PushActor(AActor* otherActor);

	UFUNCTION()
	virtual void Die();

private:
	virtual void Destroy_() { Destroy(); };

};
