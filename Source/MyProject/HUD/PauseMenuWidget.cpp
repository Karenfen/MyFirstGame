// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenuWidget.h"
#include "Components/Button.h"
#include "Components/Overlay.h"
#include "Components/CheckBox.h"
#include "../Player/TankPlayerController.h"


void UPauseMenuWidget::SetButtonClickeHandler(ATankPlayerController* handler)
{
	if (IsValid(Button_Resume))
	{
		Button_Resume->OnClicked.AddDynamic(handler, &ATankPlayerController::Unpause);
	}
	if (IsValid(Button_Quit))
	{
		Button_Quit->OnClicked.AddDynamic(handler, &ATankPlayerController::Quit);
	}
	if (IsValid(Button_Settings))
	{
		Button_Settings->OnClicked.AddDynamic(this, &UPauseMenuWidget::ShowSettingsPanel);
	}
	if (IsValid(Button_SettingsOk))
	{
		Button_SettingsOk->OnClicked.AddDynamic(this, &UPauseMenuWidget::HideSettingsPanel);
	}
	if (IsValid(CheckBox_UseGamePad))
	{
		CheckBox_UseGamePad->OnCheckStateChanged.AddDynamic(handler, &ATankPlayerController::SetGamePadControll);
	}
}

void UPauseMenuWidget::ShowSettingsPanel()
{
	if (IsValid(SettingsPanel))
	{
		SettingsPanel->SetIsEnabled(true);
		SettingsPanel->SetVisibility(ESlateVisibility::Visible);
	}
}

void UPauseMenuWidget::HideSettingsPanel()
{
	if (IsValid(SettingsPanel))
	{
		SettingsPanel->SetIsEnabled(false);
		SettingsPanel->SetVisibility(ESlateVisibility::Hidden);
	}
}