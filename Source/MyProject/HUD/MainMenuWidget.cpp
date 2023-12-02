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
		SettingsWidget->Open();
	}
	else {
		SettingsWidget = CreateWidget<UMySettingsWidget>(this, SettingsWidgetClass);
		SettingsWidget->AddToViewport(100);
	}
}

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(!IsValid(SettingsWidget)) {
		SettingsWidget = CreateWidget<UMySettingsWidget>(this, SettingsWidgetClass);
		SettingsWidget->AddToViewport(100);
	}

	if (IsValid(Button_Settings))
	{
		Button_Settings->OnClicked.AddDynamic(this, &UMainMenuWidget::OpenSettings);
	}
}

void UMainMenuWidget::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	Button_Start = nullptr;
	Button_Continue = nullptr;
	Button_Quit = nullptr;
	Button_Settings = nullptr;
	SettingsWidget = nullptr;
}
