#include "MySettingsWidget.h"
#include "MyOptionWidgetWithPercents.h"

#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/ComboBoxString.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/WidgetSwitcher.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/KismetSystemLibrary.h"





void UMySettingsWidget::UpdateGraphicsSettings()
{
	if(!IsValid(UserSettings)) {
		UserSettings = UGameUserSettings::GetGameUserSettings();
	}

	if (IsValid(UserSettings)) {
		// основные настройки графики
		if (IsValid(CheckBox_VSync)) {
			CheckBox_VSync->SetIsChecked(UserSettings->IsVSyncEnabled());
		}

		UpdateFullScreenModButtons();
		UpdateResolutionScale();
		UpdateResolution();

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

void UMySettingsWidget::Open()
{
	UpdateGraphicsSettings();
	SetVisibility(ESlateVisibility::Visible);
}

void UMySettingsWidget::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	Button_Graphic = nullptr;
	Button_Controll = nullptr;
	Button_ApplyGraphics = nullptr;
	Button_DefaultGraphics = nullptr;
	Button_ApplyControll = nullptr;
	Button_DefaultControll = nullptr;
	Button_Close = nullptr;
	WidgetSwitcher = nullptr;
	VerticalBox_Graphics = nullptr;
	VerticalBox_Controll = nullptr;
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

void UMySettingsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetVisibility(ESlateVisibility::Hidden);

	if (IsValid(Button_Graphic)) {
		Button_Graphic->OnClicked.AddDynamic(this, &UMySettingsWidget::SetActiveGraphicsPanel);
	}

	if (IsValid(Button_Controll)) {
		Button_Controll->OnClicked.AddDynamic(this, &UMySettingsWidget::SetActiveControllPanel);
	}

	if (IsValid(Button_ApplyGraphics)) {
		Button_ApplyGraphics->OnClicked.AddDynamic(this, &UMySettingsWidget::ApplyGraphicsSettings);
	}

	if (IsValid(Button_DefaultGraphics)) {
		Button_DefaultGraphics->OnClicked.AddDynamic(this, &UMySettingsWidget::SetDefaultGraphicsSettings);
	}

	if (IsValid(Button_Close)) {
		Button_Close->OnClicked.AddDynamic(this, &UMySettingsWidget::CloseSettings);
	}

	// основные настройки графики
	if (IsValid(ComboBoxString_Resolution)) {
		ComboBoxString_Resolution->OnSelectionChanged.AddDynamic(this, &UMySettingsWidget::SetResolution);
	}

	if (IsValid(Button_ScreenModeFull)) {
		Button_ScreenModeFull->OnClicked.AddDynamic(this, &UMySettingsWidget::SetScreenModeFull);
	}

	if (IsValid(Button_ScreenModeFullWindowed)) {
		Button_ScreenModeFullWindowed->OnClicked.AddDynamic(this, &UMySettingsWidget::SetScreenModeFullWindowed);
	}

	if (IsValid(Button_ScreenModeWindowed)) {
		Button_ScreenModeWindowed->OnClicked.AddDynamic(this, &UMySettingsWidget::SetScreenModeWindowed);
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

void UMySettingsWidget::CloseSettings()
{
	if (IsValid(UserSettings)) {
		UserSettings->LoadSettings();
	}
	SetVisibility(ESlateVisibility::Hidden);
}

void UMySettingsWidget::ApplyGraphicsSettings()
{
	if(IsValid(UserSettings)) {
		UserSettings->ApplySettings(true);
	}
}

void UMySettingsWidget::SetDefaultGraphicsSettings()
{
	// set defaut
	if (IsValid(UserSettings)) {
		UserSettings->SetToDefaults();
		UpdateGraphicsSettings();
	}
}

void UMySettingsWidget::SetResolution(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	// set resolution
	if (SelectionType != ESelectInfo::Direct && IsValid(UserSettings)) {
		UserSettings->SetScreenResolution(ResolutionFromString(SelectedItem));
	}

	UpdateResolutionScale();
}

void UMySettingsWidget::SetScreenModeFull()
{
	if (IsValid(UserSettings)) {
		UserSettings->SetFullscreenMode(EWindowMode::Fullscreen);
		UserSettings->ApplyResolutionSettings(true);
		UpdateFullScreenModButtons();
		UpdateResolutionScale();
		UpdateResolution();
	}
}

void UMySettingsWidget::SetScreenModeFullWindowed()
{
	if (IsValid(UserSettings)) {
		UserSettings->SetFullscreenMode(EWindowMode::WindowedFullscreen);
		UserSettings->ApplyResolutionSettings(true);
		UpdateFullScreenModButtons();
		UpdateResolutionScale();
		UpdateResolution();
	}
}

void UMySettingsWidget::SetScreenModeWindowed()
{
	if (IsValid(UserSettings)) {
		UserSettings->SetFullscreenMode(EWindowMode::Windowed);
		UserSettings->ApplyResolutionSettings(true);
		UpdateFullScreenModButtons();
		UpdateResolutionScale();
		UpdateResolution();
	}
}

void UMySettingsWidget::SetQualityAuto()
{
	// set auto
}

void UMySettingsWidget::UpdateResolutionScale()
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

void UMySettingsWidget::UpdateResolution()
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

		ComboBoxString_Resolution->SetSelectedOption(ResolutionToString(currentResolution));

	}
}

void UMySettingsWidget::UpdateFullScreenModButtons()
{
	if (IsValid(UserSettings) && IsValid(Button_ScreenModeFull) && IsValid(Button_ScreenModeFullWindowed) && IsValid(Button_ScreenModeWindowed)) {
		EWindowMode::Type screenMode = UserSettings->GetFullscreenMode();

		switch (screenMode)
		{
		case EWindowMode::Fullscreen:
			Button_ScreenModeFull->SetBackgroundColor(BackgroundColorSelected);
			Button_ScreenModeFullWindowed->SetBackgroundColor(BackgroundColorUnselected);
			Button_ScreenModeWindowed->SetBackgroundColor(BackgroundColorUnselected);
			break;
		case EWindowMode::WindowedFullscreen:
			Button_ScreenModeFull->SetBackgroundColor(BackgroundColorUnselected);
			Button_ScreenModeFullWindowed->SetBackgroundColor(BackgroundColorSelected);
			Button_ScreenModeWindowed->SetBackgroundColor(BackgroundColorUnselected);
			break;
		case EWindowMode::Windowed:
			Button_ScreenModeFull->SetBackgroundColor(BackgroundColorUnselected);
			Button_ScreenModeFullWindowed->SetBackgroundColor(BackgroundColorUnselected);
			Button_ScreenModeWindowed->SetBackgroundColor(BackgroundColorSelected);
			break;
		default:
			Button_ScreenModeFull->SetBackgroundColor(BackgroundColorUnselected);
			Button_ScreenModeFullWindowed->SetBackgroundColor(BackgroundColorUnselected);
			Button_ScreenModeWindowed->SetBackgroundColor(BackgroundColorUnselected);
			break;
		}
	}
}

FString UMySettingsWidget::ResolutionToString(const FIntPoint& resolution) const
{
	return FString::FromInt(resolution.X) + ResolutionSeporater + FString::FromInt(resolution.Y);
}

FIntPoint UMySettingsWidget::ResolutionFromString(FString& res_str)
{
	FString str_width, str_height;

	res_str.Split(ResolutionSeporater, &str_width, &str_height);

	int32 res_width = FCString::Atoi(*str_width);
	int32 res_height = FCString::Atoi(*str_height);

	return FIntPoint(res_width, res_height);
}
