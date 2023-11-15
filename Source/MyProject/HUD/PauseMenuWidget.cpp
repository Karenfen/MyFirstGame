// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenuWidget.h"
#include "Components/Button.h"
#include "Components/Overlay.h"
#include "Components/CheckBox.h"
#include "../Player/TankPlayerController.h"
#include "MySettingsWidget.h"




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
	if (IsValid(Button_Save))
	{
		Button_Save->OnClicked.AddDynamic(handler, &ATankPlayerController::SaveGame);
	}
}

void UPauseMenuWidget::OpenSettings()
{
	if (IsValid(SettingsWidget)) {
		SettingsWidget->AddToViewport();
	}
}

void UPauseMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SettingsWidget = CreateWidget<UMySettingsWidget>(this, SettingsWidgetClass);

	if (IsValid(Button_Settings))
	{
		Button_Settings->OnClicked.AddDynamic(this, &UPauseMenuWidget::OpenSettings);
	}

}
