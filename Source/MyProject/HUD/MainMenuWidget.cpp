// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "Components/Button.h"
#include "../MainMenuLevelScriptActor.h"
#include "MySettingsWidget.h"



void UMainMenuWidget::SetButtonClickeHandler(AMainMenuLevelScriptActor* mainMenuLevel)
{
	if (IsValid(Button_Start))
	{
		Button_Start->OnClicked.AddDynamic(mainMenuLevel, &AMainMenuLevelScriptActor::StartClicked);
	}
	if (IsValid(Button_Continue))
	{
		Button_Continue->OnClicked.AddDynamic(mainMenuLevel, &AMainMenuLevelScriptActor::ContinueCliced);
	}
	if (IsValid(Button_Quit))
	{
		Button_Quit->OnClicked.AddDynamic(mainMenuLevel, &AMainMenuLevelScriptActor::QuitClicked);
	}
	if (IsValid(Button_Settings))
	{
		Button_Settings->OnClicked.AddDynamic(this, &UMainMenuWidget::OpenSettings);
	}

	if (IsValid(SettingsWidget)) {
		SettingsWidget->SetButtonClickeHandler();
	}
}

void UMainMenuWidget::SetContinueButtonIsAnabled(bool isAnabled)
{
	if (IsValid(Button_Continue))
	{
		Button_Continue->SetIsEnabled(isAnabled);

		if(isAnabled)
		{
			Button_Continue->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			Button_Continue->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UMainMenuWidget::OpenSettings()
{
	if (IsValid(SettingsWidget)) {
		SettingsWidget->SetVisibility(ESlateVisibility::Visible);
	}
}
