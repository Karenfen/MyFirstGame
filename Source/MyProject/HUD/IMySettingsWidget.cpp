#include "IMySettingsWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GameFramework/GameUserSettings.h"






void UIMySettingsWidget::UpdateSettings()
{

}

void UIMySettingsWidget::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	Button_Apply = nullptr;
	Button_Default = nullptr;
}

void UIMySettingsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!IsValid(UserSettings)) {
		UserSettings = UGameUserSettings::GetGameUserSettings();
	}

	if (IsValid(TextBlock_Name)) {
		TextBlock_Name->SetText(Name);
	}

	if (IsValid(Button_Apply)) {
		Button_Apply->OnClicked.AddDynamic(this, &UIMySettingsWidget::ApplySettings);
	}

	if (IsValid(Button_Default)) {
		Button_Default->OnClicked.AddDynamic(this, &UIMySettingsWidget::SetDefaultSettings);
	}
}

void UIMySettingsWidget::Cancel()
{
	if (IsValid(UserSettings)) {
		UserSettings->LoadSettings();
	}
}

void UIMySettingsWidget::ApplySettings()
{
	if (IsValid(UserSettings)) {
		UserSettings->ApplyNonResolutionSettings();
		UserSettings->SaveSettings();
	}
}

void UIMySettingsWidget::SetDefaultSettings()
{
	if (IsValid(UserSettings)) {
		UserSettings->SetToDefaults();
		UpdateSettings();
	}
}