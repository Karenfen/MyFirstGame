// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "MySettingsWidget.generated.h"

class UButton;
class UWidgetSwitcher;
class UVerticalBox;
class UCheckBox;
class UTextBlock;
class UMyOptionWidget;
class UMyOptionWidgetWithPercents;
class UComboBoxString;


UCLASS()
class MYPROJECT_API UMySettingsWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* Button_Graphic;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* Button_Controll;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* Button_ApplyGraphics;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* Button_DefaultGraphics;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* Button_ApplyControll;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* Button_DefaultControll;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* Button_Close;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UWidgetSwitcher* WidgetSwitcher;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UVerticalBox* VerticalBox_Graphics;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UVerticalBox* VerticalBox_Controll;

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Select Color", meta = (sRGB = "true"))
	FLinearColor BackgroundColorSelected;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Select Color", meta = (sRGB = "true"))
	FLinearColor BackgroundColorUnselected;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Select Color")
	FString ResolutionSeporater;

public:
	void UpdateGraphicsSettings();
	UFUNCTION()
	void Open();

protected:
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	virtual void NativeConstruct() override;

	UFUNCTION()
	void SetActiveGraphicsPanel();
	UFUNCTION()
	void SetActiveControllPanel();
	UFUNCTION()
	void CloseSettings();

	// graphics settings setters
	UFUNCTION()
	void ApplyGraphicsSettings();
	UFUNCTION()
	void SetDefaultGraphicsSettings();
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

protected:
	class UGameUserSettings* UserSettings {nullptr};
};
