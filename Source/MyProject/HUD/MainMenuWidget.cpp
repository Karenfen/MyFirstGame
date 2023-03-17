// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "Components/Button.h"
#include "../MainMenuLevelScriptActor.h"



void UMainMenuWidget::SetButtonClickeHandler(AMainMenuLevelScriptActor* mainMenuLevel)
{
	if (IsValid(Button_Start))
	{
		Button_Start->OnClicked.AddDynamic(mainMenuLevel, &AMainMenuLevelScriptActor::StartClicked);
	}
	if (IsValid(Button_Quit))
	{
		Button_Quit->OnClicked.AddDynamic(mainMenuLevel, &AMainMenuLevelScriptActor::QuitClicked);
	}
}
