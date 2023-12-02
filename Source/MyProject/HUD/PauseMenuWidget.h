// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenuWidget.generated.h"


class UButton;
class UOverlay;
class UCheckBox;
class UMySettingsWidget;

UCLASS()
class MYPROJECT_API UPauseMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* Button_Resume;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* Button_Quit;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* Button_Settings;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* Button_Save;

	UPROPERTY(EditAnywhere)
	UMySettingsWidget* SettingsWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	TSubclassOf<UMySettingsWidget> SettingsWidgetClass;

public:
	void SetButtonClickeHandler(class ATankPlayerController* handler);
	UFUNCTION()
	void Open();
	UFUNCTION()
	void Close();

protected:
	UFUNCTION()
	void OpenSettings();
	virtual void NativeConstruct() override;
};
