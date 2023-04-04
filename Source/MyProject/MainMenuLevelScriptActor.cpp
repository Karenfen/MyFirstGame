// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuLevelScriptActor.h"
#include "MenuPlayerController.h"
#include "HUD/MainMenuWidget.h"
#include <Kismet/GameplayStatics.h>
#include "Kismet/KismetSystemLibrary.h"
#include "SavePlayerState.h"
#include "MySaveGame.h"



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

	SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot("Save game", 1));

	if (IsValid(SaveGameInstance))
	{
		if (SaveGameInstance->IsEmpty())
		{
			Menu->SetContinueButtonIsAnabled(false);
			SaveGameInstance = nullptr;
		}
		else
		{
			Menu->SetContinueButtonIsAnabled(true);
		}
	}
	else
	{
		Menu->SetContinueButtonIsAnabled(false);
		SaveGameInstance = nullptr;
	}
}

void AMainMenuLevelScriptActor::StartClicked()
{
	USavePlayerState* savePlayerInstance = Cast<USavePlayerState>(UGameplayStatics::CreateSaveGameObject(USavePlayerState::StaticClass()));
	if (IsValid(savePlayerInstance))
	{
		savePlayerInstance->SavePlayerState(FPlayerTankState());
		UGameplayStatics::SaveGameToSlot(savePlayerInstance, TEXT("Player state"), 0);
	}

	UGameplayStatics::OpenLevel(GetWorld(), LoadLevelName);
}

void AMainMenuLevelScriptActor::QuitClicked()
{
	UKismetSystemLibrary::QuitGame(this, MenuController, EQuitPreference::Quit, true);
}

void AMainMenuLevelScriptActor::ContinueCliced()
{
	if (IsValid(SaveGameInstance))
	{
		if (SaveGameInstance->IsEmpty())
		{
			return;
		}

		USavePlayerState* savePlayerInstance = Cast<USavePlayerState>(UGameplayStatics::CreateSaveGameObject(USavePlayerState::StaticClass()));
		if (IsValid(savePlayerInstance))
		{
			savePlayerInstance->SavePlayerState(SaveGameInstance->GetPlayerState());
			UGameplayStatics::SaveGameToSlot(savePlayerInstance, TEXT("Player state"), 0);

			UGameplayStatics::OpenLevel(GetWorld(), SaveGameInstance->LoadLevel());
		}
	}
}
