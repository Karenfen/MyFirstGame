#include "MapLoader.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"


AMapLoader::AMapLoader()
{
	USceneComponent* sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = sceneComp;

	GatesMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gates Mesh"));
	GatesMesh->SetupAttachment(sceneComp);

	ActivatedLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Activated lights"));
	ActivatedLight->SetupAttachment(sceneComp);

	DeactivatedLight =	CreateDefaultSubobject<UPointLightComponent>(TEXT("Deactivated lights"));
	DeactivatedLight->SetupAttachment(sceneComp);

	TriggerCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger	collider"));
	TriggerCollider->SetupAttachment(sceneComp);
	TriggerCollider->OnComponentBeginOverlap.AddDynamic(this,	&AMapLoader::OnTriggerOverlapBegin);

	SetActiveLights();
}

void AMapLoader::SetIsActivated(bool NewIsActivated)
{
	IsActivated = NewIsActivated;
	SetActiveLights();
}

void AMapLoader::SetActiveLights()
{
	ActivatedLight->SetHiddenInGame(!IsActivated);
	DeactivatedLight->SetHiddenInGame(IsActivated);
}

void AMapLoader::OnTriggerOverlapBegin(UPrimitiveComponent* OverlappedComp, 
	AActor*	OtherActor,	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
	bool bFromSweep, const	FHitResult& SweepResult)
{
	if (!IsActivated)
		return;

	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (OtherActor == PlayerPawn)
	{
		//if(!Boss)
		//	UGameplayStatics::OpenLevel(GetWorld(), LoadLevelName);
		//else
		//	if(Boss->IsReadyForFinishDestroy())
		//		UGameplayStatics::OpenLevel(GetWorld(), LoadLevelName);
		UGameplayStatics::OpenLevel(GetWorld(), LoadLevelName);
	}
}

void AMapLoader::BeginPlay()
{
	Super::BeginPlay();
	SetActiveLights();
}