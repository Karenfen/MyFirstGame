// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ComboBoxKey.h"
#include "MySettingsWidget.generated.h"

class UButton;
class UWidgetSwitcher;
class UVerticalBox;


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

	// graphics buttons
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UComboBoxKey* ComboBoxKey_Resolution;

public:
	void LoadGraphicsSettings();

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void SetActiveGraphicsPanel();
	UFUNCTION()
	void SetActiveControllPanel();

	// graphics settings setters
	UFUNCTION()
	void ApplyGraphicsSettings();
	UFUNCTION()
	void SetDefaultGraphicsSettings();

	void SetResolution(FName SelectedItem, ESelectInfo::Type SelectionType);
};
