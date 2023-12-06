#include "MyGraphicSettingsWidget.h"
#include "MyOptionWidgetWithPercents.h"

#include "Components/CheckBox.h"
#include "Components/Button.h"
#include "Components/ComboBoxString.h"
#include "Components/Slider.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/KismetSystemLibrary.h"


void UMyGraphicSettingsWidget::UpdateSettings()
{
	Super::UpdateSettings();

	if (IsValid(UserSettings)) {
		// основные настройки графики
		if (IsValid(CheckBox_VSync)) {
			CheckBox_VSync->SetIsChecked(UserSettings->IsVSyncEnabled());
		}

		UpdateFullScreenModButtons();
		UpdateResolution();
		UpdateResolutionScale();

		// расширенные настройки графики
		if (IsValid(BP_OptionWidget_ViewDistance)) {
			BP_OptionWidget_ViewDistance->SetOptionState(UserSettings->GetViewDistanceQuality());
		}
		if (IsValid(BP_OptionWidget_AntiAliasing)) {
			BP_OptionWidget_AntiAliasing->SetOptionState(UserSettings->GetAntiAliasingQuality());
		}
		if (IsValid(BP_OptionWidget_PostProcessing)) {
			BP_OptionWidget_PostProcessing->SetOptionState(UserSettings->GetPostProcessingQuality());
		}
		if (IsValid(BP_OptionWidget_Shadows)) {
			BP_OptionWidget_Shadows->SetOptionState(UserSettings->GetShadowQuality());
		}
		if (IsValid(BP_OptionWidget_GlobalIllumination)) {
			BP_OptionWidget_GlobalIllumination->SetOptionState(UserSettings->GetGlobalIlluminationQuality());
		}
		if (IsValid(BP_OptionWidget_Reflections)) {
			BP_OptionWidget_Reflections->SetOptionState(UserSettings->GetReflectionQuality());
		}
		if (IsValid(BP_OptionWidget_Textures)) {
			BP_OptionWidget_Textures->SetOptionState(UserSettings->GetTextureQuality());
		}
		if (IsValid(BP_OptionWidget_Effects)) {
			BP_OptionWidget_Effects->SetOptionState(UserSettings->GetVisualEffectQuality());
		}
		if (IsValid(BP_OptionWidget_Foliage)) {
			BP_OptionWidget_Foliage->SetOptionState(UserSettings->GetFoliageQuality());
		}
		if (IsValid(BP_OptionWidget_Shading)) {
			BP_OptionWidget_Shading->SetOptionState(UserSettings->GetShadingQuality());
		}
	}
}

void UMyGraphicSettingsWidget::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	ComboBoxString_Resolution = nullptr;
	Button_ScreenModeFull = nullptr;
	Button_ScreenModeFullWindowed = nullptr;
	Button_ScreenModeWindowed = nullptr;
	CheckBox_VSync = nullptr;

	BP_OptionWidgetWithPercents_ResolutionScale = nullptr;
	BP_OptionWidget_ViewDistance = nullptr;
	BP_OptionWidget_AntiAliasing = nullptr;
	BP_OptionWidget_PostProcessing = nullptr;
	BP_OptionWidget_Shadows = nullptr;
	BP_OptionWidget_GlobalIllumination = nullptr;
	BP_OptionWidget_Reflections = nullptr;
	BP_OptionWidget_Textures = nullptr;
	BP_OptionWidget_Effects = nullptr;
	BP_OptionWidget_Foliage = nullptr;
	BP_OptionWidget_Shading = nullptr;
}

void UMyGraphicSettingsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// основные настройки графики
	if (IsValid(ComboBoxString_Resolution)) {
		ComboBoxString_Resolution->OnSelectionChanged.AddDynamic(this, &UMyGraphicSettingsWidget::SetResolution);
	}

	if (IsValid(Button_ScreenModeFull)) {
		Button_ScreenModeFull->OnClicked.AddDynamic(this, &UMyGraphicSettingsWidget::SetScreenModeFull);
	}

	if (IsValid(Button_ScreenModeFullWindowed)) {
		Button_ScreenModeFullWindowed->OnClicked.AddDynamic(this, &UMyGraphicSettingsWidget::SetScreenModeFullWindowed);
	}

	if (IsValid(Button_ScreenModeWindowed)) {
		Button_ScreenModeWindowed->OnClicked.AddDynamic(this, &UMyGraphicSettingsWidget::SetScreenModeWindowed);
	}

	if (IsValid(UserSettings)) {

		if (IsValid(CheckBox_VSync)) {
			CheckBox_VSync->OnCheckStateChanged.AddDynamic(UserSettings, &UGameUserSettings::SetVSyncEnabled);
		}

		if (IsValid(BP_OptionWidgetWithPercents_ResolutionScale)) {
			BP_OptionWidgetWithPercents_ResolutionScale->OnPercentsChanged.AddUObject(UserSettings, &UGameUserSettings::SetResolutionScaleValueEx);
		}

		// расширенные настройки графики

		if (IsValid(BP_OptionWidget_ViewDistance)) {
			BP_OptionWidget_ViewDistance->OnValueChanged.AddUObject(UserSettings, &UGameUserSettings::SetViewDistanceQuality);
		}
		if (IsValid(BP_OptionWidget_AntiAliasing)) {
			BP_OptionWidget_AntiAliasing->OnValueChanged.AddUObject(UserSettings, &UGameUserSettings::SetAntiAliasingQuality);
		}
		if (IsValid(BP_OptionWidget_PostProcessing)) {
			BP_OptionWidget_PostProcessing->OnValueChanged.AddUObject(UserSettings, &UGameUserSettings::SetPostProcessingQuality);
		}
		if (IsValid(BP_OptionWidget_Shadows)) {
			BP_OptionWidget_Shadows->OnValueChanged.AddUObject(UserSettings, &UGameUserSettings::SetShadowQuality);
		}
		if (IsValid(BP_OptionWidget_GlobalIllumination)) {
			BP_OptionWidget_GlobalIllumination->OnValueChanged.AddUObject(UserSettings, &UGameUserSettings::SetGlobalIlluminationQuality);
		}
		if (IsValid(BP_OptionWidget_Reflections)) {
			BP_OptionWidget_Reflections->OnValueChanged.AddUObject(UserSettings, &UGameUserSettings::SetReflectionQuality);
		}
		if (IsValid(BP_OptionWidget_Textures)) {
			BP_OptionWidget_Textures->OnValueChanged.AddUObject(UserSettings, &UGameUserSettings::SetTextureQuality);
		}
		if (IsValid(BP_OptionWidget_Effects)) {
			BP_OptionWidget_Effects->OnValueChanged.AddUObject(UserSettings, &UGameUserSettings::SetVisualEffectQuality);
		}
		if (IsValid(BP_OptionWidget_Foliage)) {
			BP_OptionWidget_Foliage->OnValueChanged.AddUObject(UserSettings, &UGameUserSettings::SetFoliageQuality);
		}
		if (IsValid(BP_OptionWidget_Shading)) {
			BP_OptionWidget_Shading->OnValueChanged.AddUObject(UserSettings, &UGameUserSettings::SetShadingQuality);
		}
	}
}

void UMyGraphicSettingsWidget::ApplySettings()
{
	if (IsValid(UserSettings)) {
		UserSettings->ApplySettings(true);
	}
}

void UMyGraphicSettingsWidget::SetResolution(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	if (SelectedItem.IsEmpty()) {
		return;
	}

	if (IsValid(UserSettings)) {
		UserSettings->SetScreenResolution(ResolutionFromString(SelectedItem));
	}

	UpdateResolutionScale();
}

void UMyGraphicSettingsWidget::SetScreenModeFull()
{
	if (IsValid(UserSettings)) {
		UserSettings->SetFullscreenMode(EWindowMode::Fullscreen);

		UpdateResolution();
		UpdateFullScreenModButtons();
	}
}

void UMyGraphicSettingsWidget::SetScreenModeFullWindowed()
{
	if (IsValid(UserSettings)) {
		UserSettings->SetFullscreenMode(EWindowMode::WindowedFullscreen);

		UpdateResolution();
		UpdateFullScreenModButtons();
	}
}

void UMyGraphicSettingsWidget::SetScreenModeWindowed()
{
	if (IsValid(UserSettings)) {
		UserSettings->SetFullscreenMode(EWindowMode::Windowed);

		UpdateResolution();
		UpdateFullScreenModButtons();
	}
}

void UMyGraphicSettingsWidget::SetQualityAuto()
{
}

void UMyGraphicSettingsWidget::UpdateResolutionScale()
{
	if (IsValid(BP_OptionWidgetWithPercents_ResolutionScale)) {
		float CurrentScaleNormalized;
		float CurrentScaleValue;
		float minScaleValue;
		float maxScaleValue;

		UserSettings->GetResolutionScaleInformationEx(CurrentScaleNormalized, CurrentScaleValue, minScaleValue, maxScaleValue);

		BP_OptionWidgetWithPercents_ResolutionScale->SetRange(minScaleValue, maxScaleValue);
		BP_OptionWidgetWithPercents_ResolutionScale->SetOptionState(CurrentScaleValue);
	}
}

void UMyGraphicSettingsWidget::UpdateResolution()
{
	if (IsValid(ComboBoxString_Resolution) && IsValid(UserSettings)) {
		ComboBoxString_Resolution->ClearOptions();

		TArray<FIntPoint> Resolutions;

		if (UserSettings->GetFullscreenMode() == EWindowMode::Windowed) {
			UKismetSystemLibrary::GetConvenientWindowedResolutions(Resolutions);
		}
		else {
			UKismetSystemLibrary::GetSupportedFullscreenResolutions(Resolutions);
		}

		for (const auto& resolution : Resolutions) {
			ComboBoxString_Resolution->AddOption(ResolutionToString(resolution));
		}

		FIntPoint currentResolution = UserSettings->GetScreenResolution();

		if (ComboBoxString_Resolution->FindOptionIndex(ResolutionToString(currentResolution)) == -1) {
			currentResolution = *(Resolutions.begin());
		}

		ComboBoxString_Resolution->SetSelectedOption(ResolutionToString(currentResolution));
	}
}

void UMyGraphicSettingsWidget::UpdateFullScreenModButtons()
{
	if (IsValid(UserSettings) && IsValid(Button_ScreenModeFull) && IsValid(Button_ScreenModeFullWindowed) && IsValid(Button_ScreenModeWindowed)) {
		EWindowMode::Type screenMode = UserSettings->GetFullscreenMode();

		switch (screenMode)
		{
		case EWindowMode::Fullscreen:
			Button_ScreenModeFull->SetIsEnabled(false);
			Button_ScreenModeFull->SetBackgroundColor(BackgroundColorSelected);

			Button_ScreenModeFullWindowed->SetIsEnabled(true);
			Button_ScreenModeFullWindowed->SetBackgroundColor(BackgroundColorUnselected);

			Button_ScreenModeWindowed->SetIsEnabled(true);
			Button_ScreenModeWindowed->SetBackgroundColor(BackgroundColorUnselected);
			break;

		case EWindowMode::WindowedFullscreen:
			Button_ScreenModeFull->SetIsEnabled(true);
			Button_ScreenModeFull->SetBackgroundColor(BackgroundColorUnselected);

			Button_ScreenModeFullWindowed->SetIsEnabled(false);
			Button_ScreenModeFullWindowed->SetBackgroundColor(BackgroundColorSelected);

			Button_ScreenModeWindowed->SetIsEnabled(true);
			Button_ScreenModeWindowed->SetBackgroundColor(BackgroundColorUnselected);
			break;

		case EWindowMode::Windowed:
			Button_ScreenModeFull->SetIsEnabled(true);
			Button_ScreenModeFull->SetBackgroundColor(BackgroundColorUnselected);

			Button_ScreenModeFullWindowed->SetIsEnabled(true);
			Button_ScreenModeFullWindowed->SetBackgroundColor(BackgroundColorUnselected);

			Button_ScreenModeWindowed->SetIsEnabled(false);
			Button_ScreenModeWindowed->SetBackgroundColor(BackgroundColorSelected);

			break;
		}
	}
}

FString UMyGraphicSettingsWidget::ResolutionToString(const FIntPoint& resolution) const
{
	return FString::FromInt(resolution.X) + ResolutionSeporater + FString::FromInt(resolution.Y);
}

FIntPoint UMyGraphicSettingsWidget::ResolutionFromString(FString& res_str)
{
	FString str_width, str_height;

	res_str.Split(ResolutionSeporater, &str_width, &str_height);

	int32 res_width = FCString::Atoi(*str_width);
	int32 res_height = FCString::Atoi(*str_height);

	return FIntPoint(res_width, res_height);
}
