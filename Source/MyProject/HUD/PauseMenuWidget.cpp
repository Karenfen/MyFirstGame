// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenuWidget.h"
#include "Components/Button.h"
#include "Components/Overlay.h"
#include "Components/CheckBox.h"
#include "Components/Slider.h"
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

void UPauseMenuWidget::Open()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UPauseMenuWidget::Close()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UPauseMenuWidget::OpenSettings()
{
	if (IsValid(SettingsWidget)) {
		SettingsWidget->Open();
	}
	else {
		SettingsWidget = CreateWidget<UMySettingsWidget>(this, SettingsWidgetClass);
		SettingsWidget->AddToViewport(100);
	}
}

void UPauseMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetVisibility(ESlateVisibility::Hidden);

	if(!IsValid(SettingsWidget))	{
		SettingsWidget = CreateWidget<UMySettingsWidget>(this, SettingsWidgetClass);
		SettingsWidget->AddToViewport(100);
	}

	if (IsValid(Button_Settings))
	{
		Button_Settings->OnClicked.AddDynamic(this, &UPauseMenuWidget::OpenSettings);
	}

}
