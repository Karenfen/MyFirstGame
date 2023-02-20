#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseAmmoClass.h"
#include "Projectile.generated.h"

UCLASS()
class MYPROJECT_API AProjectile : public ABaseAmmoClass
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
	float MoveSpeed = 500;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
	float MoveRate = 0.005f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
	float PushForce = 1000;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage|Explode")
	float ExplodeRadius = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage|Explode")
	bool ExplodeAvailable = false;

	// ��������� ���������� ������ ������
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Effects")
	class UParticleSystemComponent* ExplodeEffect;

	// ��������� ����� ������ ������
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Effects")
	class UAudioComponent* ExplodeAudio;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Live")
	float TimeToDestroyAfterHit = 1.0f;

	FTimerHandle MovementTimerHandle;
	
public:	
	AProjectile();
	virtual ~AProjectile();
	virtual void Start() override;

protected:
	UFUNCTION()
	virtual void OnMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor*
			OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool
			bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void Move();

	UFUNCTION()
	virtual void Explode();

	// ����� �� ������������ �������
	UFUNCTION()
	bool PushActor(AActor* otherActor);

	UFUNCTION()
	virtual void Die();

	UFUNCTION()
	bool MakeDamageTo(AActor* otherActor);

	virtual void Destroy_() override;

};
