#include "MySettingsMenuWidget.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "MyAudioSettingsWidget.h"
#include "MyGraphicSettingsWidget.h"
#include "MyControllSettingsWidget.h"




void UMySettingsMenuWidget::Open()
{
	SetActiveGraphicsPanel();
	SetVisibility(ESlateVisibility::Visible);
}

void UMySettingsMenuWidget::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	Button_Graphic = nullptr;
	Button_Controll = nullptr;
	Button_Audio = nullptr;
	Button_Close = nullptr;
	WidgetSwitcher = nullptr;
	BP_GraphicsSettingsWidget = nullptr;
	BP_ControllSettingsWidget = nullptr;
	BP_AudioSettingsWidget = nullptr;
}

void UMySettingsMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetVisibility(ESlateVisibility::Hidden);

	if (IsValid(Button_Graphic)) {
		Button_Graphic->OnClicked.AddDynamic(this, &UMySettingsMenuWidget::SetActiveGraphicsPanel);
	}

	if (IsValid(Button_Controll)) {
		Button_Controll->OnClicked.AddDynamic(this, &UMySettingsMenuWidget::SetActiveControllPanel);
	}

	if (IsValid(Button_Audio)) {
		Button_Audio->OnClicked.AddDynamic(this, &UMySettingsMenuWidget::SetActiveAudioPanel);
	}

	if (IsValid(Button_Close)) {
		Button_Close->OnClicked.AddDynamic(this, &UMySettingsMenuWidget::CloseMenu);
	}
}

void UMySettingsMenuWidget::SetActiveGraphicsPanel()
{
	if (IsValid(WidgetSwitcher) && IsValid(BP_GraphicsSettingsWidget)) {
		WidgetSwitcher->SetActiveWidget(BP_GraphicsSettingsWidget);

		BP_GraphicsSettingsWidget->Cancel();
		BP_GraphicsSettingsWidget->UpdateSettings();
	}
}

void UMySettingsMenuWidget::SetActiveControllPanel()
{
	if (IsValid(WidgetSwitcher) && IsValid(BP_ControllSettingsWidget)) {
		WidgetSwitcher->SetActiveWidget(BP_ControllSettingsWidget);

		BP_ControllSettingsWidget->Cancel();
		BP_ControllSettingsWidget->UpdateSettings();
	}
}

void UMySettingsMenuWidget::SetActiveAudioPanel()
{
	if (IsValid(WidgetSwitcher) && IsValid(BP_AudioSettingsWidget)) {
		WidgetSwitcher->SetActiveWidget(BP_AudioSettingsWidget);

		BP_AudioSettingsWidget->Cancel();
		BP_AudioSettingsWidget->UpdateSettings();
	}
}

void UMySettingsMenuWidget::CloseMenu()
{
	SetVisibility(ESlateVisibility::Hidden);

	if (IsValid(BP_GraphicsSettingsWidget)) {
		BP_GraphicsSettingsWidget->Cancel();
	}

	if (IsValid(BP_ControllSettingsWidget)) {
		BP_ControllSettingsWidget->Cancel();
	}

	if (IsValid(BP_AudioSettingsWidget)) {
		BP_AudioSettingsWidget->Cancel();
	}
}