// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuLevelScriptActor.h"
#include "MenuPlayerController.h"
#include "HUD/MainMenuWidget.h"
#include <Kismet/GameplayStatics.h>
#include "Kismet/KismetSystemLibrary.h"
#include "SavePlayerState.h"



void AMainMenuLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();

	MenuController = Cast<AMenuPlayerController>(GetWorld()->GetFirstPlayerController());

	if(IsValid(MenuController))
	{
		Menu = CreateWidget<UMainMenuWidget>(MenuController, MenuClass);

		if (IsValid(Menu))
		{
			Menu->AddToViewport();
			Menu->SetButtonClickeHandler(this);
		}
	}

	USavePlayerState* savePlayerInstance = Cast<USavePlayerState>(UGameplayStatics::CreateSaveGameObject(USavePlayerState::StaticClass()));
	if (IsValid(savePlayerInstance))
	{
		savePlayerInstance->SetAvailability(false);
		UGameplayStatics::SaveGameToSlot(savePlayerInstance, TEXT("Player state"), 0);
	}
}

void AMainMenuLevelScriptActor::StartClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), LoadLevelName);
}

void AMainMenuLevelScriptActor::QuitClicked()
{
	UKismetSystemLibrary::QuitGame(this, MenuController, EQuitPreference::Quit, true);
}
