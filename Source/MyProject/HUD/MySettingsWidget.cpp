// Fill out your copyright notice in the Description page of Project Settings.


#include "MySettingsWidget.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"




void UMySettingsWidget::LoadGraphicsSettings()
{
}

void UMySettingsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	LoadGraphicsSettings();

	if (IsValid(Button_Graphic)) {
		Button_Graphic->OnClicked.AddDynamic(this, &UMySettingsWidget::SetActiveGraphicsPanel);
	}

	if (IsValid(Button_Controll)) {
		Button_Controll->OnClicked.AddDynamic(this, &UMySettingsWidget::SetActiveControllPanel);
	}

	if (IsValid(Button_ApplyGraphics)) {
		Button_ApplyGraphics->OnClicked.AddDynamic(this, &UMySettingsWidget::ApplyGraphicsSettings);
	}

	if (IsValid(Button_Close)) {
		Button_Close->OnClicked.AddDynamic(this, &UMySettingsWidget::RemoveFromViewport);
	}

	// graphics buttons
	if (IsValid(ComboBoxKey_Resolution)) {
		ComboBoxKey_Resolution->OnSelectionChanged.AddDynamic(this, &UMySettingsWidget::SetResolution);
	}
}

void UMySettingsWidget::SetActiveGraphicsPanel()
{
	if (IsValid(WidgetSwitcher) && IsValid(VerticalBox_Graphics)) {
		WidgetSwitcher->SetActiveWidget(VerticalBox_Graphics);
	}
}

void UMySettingsWidget::SetActiveControllPanel()
{
	if (IsValid(WidgetSwitcher) && IsValid(VerticalBox_Controll)) {
		WidgetSwitcher->SetActiveWidget(VerticalBox_Controll);
	}
}

void UMySettingsWidget::ApplyGraphicsSettings()
{
	// save

}

void UMySettingsWidget::SetDefaultGraphicsSettings()
{
	// set defaut

}

void UMySettingsWidget::SetResolution(FName SelectedItem, ESelectInfo::Type SelectionType)
{
	// set resolution
	
}