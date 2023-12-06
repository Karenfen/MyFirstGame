#pragma once

#include "CoreMinimal.h"
#include "IMySettingsWidget.h"
#include "MyGraphicSettingsWidget.generated.h"

class UButton;
class UComboBoxString;
class UCheckBox;
class UMyOptionWidgetWithPercents;
class UMyOptionWidget;



UCLASS()
class MYPROJECT_API UMyGraphicSettingsWidget : public UIMySettingsWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* Button_Auto;

	// элементы настройки графики (основные)
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UComboBoxString* ComboBoxString_Resolution;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* Button_ScreenModeFull;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* Button_ScreenModeFullWindowed;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* Button_ScreenModeWindowed;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UCheckBox* CheckBox_VSync;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UMyOptionWidgetWithPercents* BP_OptionWidgetWithPercents_ResolutionScale;

	// элементы настройки графики (расширенные)
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UMyOptionWidget* BP_OptionWidget_ViewDistance;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UMyOptionWidget* BP_OptionWidget_AntiAliasing;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UMyOptionWidget* BP_OptionWidget_PostProcessing;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UMyOptionWidget* BP_OptionWidget_Shadows;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UMyOptionWidget* BP_OptionWidget_GlobalIllumination;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UMyOptionWidget* BP_OptionWidget_Reflections;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UMyOptionWidget* BP_OptionWidget_Textures;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UMyOptionWidget* BP_OptionWidget_Effects;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UMyOptionWidget* BP_OptionWidget_Foliage;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UMyOptionWidget* BP_OptionWidget_Shading;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Variables", meta = (sRGB = "true"))
	FLinearColor BackgroundColorSelected;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Variables", meta = (sRGB = "true"))
	FLinearColor BackgroundColorUnselected;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Variables")
	FString ResolutionSeporater;
	
public:
	virtual void UpdateSettings() override;

protected:
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	virtual void NativeConstruct() override;
	virtual void ApplySettings() override;
	UFUNCTION()
	void SetResolution(FString SelectedItem, ESelectInfo::Type SelectionType);
	UFUNCTION()
	void SetScreenModeFull();
	UFUNCTION()
	void SetScreenModeFullWindowed();
	UFUNCTION()
	void SetScreenModeWindowed();
	UFUNCTION()
	void SetQualityAuto();
	void UpdateResolutionScale();
	void UpdateResolution();
	void UpdateFullScreenModButtons();
	FString ResolutionToString(const FIntPoint& resolution) const;
	FIntPoint ResolutionFromString(FString& res_str);
};
