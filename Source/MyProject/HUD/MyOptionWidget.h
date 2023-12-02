// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Containers/Map.h"
#include "MyOptionWidget.generated.h"

class USlider;
class UTextBlock;


const TMap<float, FText> OptionState {
	{0.0f, FText::FromString("Low")},
	{1.0f, FText::FromString("Medium")},
	{2.0f, FText::FromString("High")},
	{3.0f, FText::FromString("Epic")}
};



UCLASS()
class MYPROJECT_API UMyOptionWidget : public UUserWidget
{
	GENERATED_BODY()

	DECLARE_EVENT_OneParam(UMyOptionWidget, FOnOptionValueChangedEvent, int32);

public:
	// вызывается когда нужно изменить настройку
	FOnOptionValueChangedEvent OnValueChanged;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	USlider* Slider_Option;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* TextBlock_OptionState;

public:
	UFUNCTION()
	virtual void SetOptionState(float state);
	UFUNCTION()
	virtual void ValueSwitchedHandler(float newValue);
	UFUNCTION()
	virtual void ValueChangedHandler();

protected:
	virtual void NativeConstruct() override;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

};
