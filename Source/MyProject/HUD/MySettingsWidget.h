// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MySettingsWidget.generated.h"

class UButton;
class UWidgetSwitcher;
class UScrollBox;


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
	UButton* Button_Ok;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* Button_Cancel;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UWidgetSwitcher* WidgetSwitcher;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UScrollBox* ScrollBox_Graphics;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UScrollBox* ScrollBox_Controll;

public:
	void SetButtonClickeHandler();

protected:
	UFUNCTION()
	void SetActiveGraphicsPanel();
	UFUNCTION()
	void SetActiveControllPanel();
	UFUNCTION()
	void Ok();
	UFUNCTION()
	void Cancel();
};
