// Fill out your copyright notice in the Description page of Project Settings.


#include "MySettingsWidget.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"


void UMySettingsWidget::SetButtonClickeHandler()
{
	if (IsValid(Button_Graphic)) {
		Button_Graphic->OnClicked.AddDynamic(this, &UMySettingsWidget::SetActiveGraphicsPanel);
	}

	if (IsValid(Button_Controll)) {
		Button_Controll->OnClicked.AddDynamic(this, &UMySettingsWidget::SetActiveControllPanel);
	}

	if (IsValid(Button_Ok)) {
		Button_Ok->OnClicked.AddDynamic(this, &UMySettingsWidget::Ok);
	}

	if (IsValid(Button_Cancel)) {
		Button_Cancel->OnClicked.AddDynamic(this, &UMySettingsWidget::Cancel);
	}
}

void UMySettingsWidget::SetActiveGraphicsPanel()
{
	if (IsValid(WidgetSwitcher) && IsValid(ScrollBox_Graphics)) {
		WidgetSwitcher->SetActiveWidget(ScrollBox_Graphics);
	}
}

void UMySettingsWidget::SetActiveControllPanel()
{
	if (IsValid(WidgetSwitcher) && IsValid(ScrollBox_Controll)) {
		WidgetSwitcher->SetActiveWidget(ScrollBox_Controll);
	}
}

void UMySettingsWidget::Ok()
{
	// save
	if (IsValid(this)) {
		this->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UMySettingsWidget::Cancel()
{
	// reset
	if (IsValid(this)) {
		this->SetVisibility(ESlateVisibility::Hidden);
	}
}
