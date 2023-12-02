// Fill out your copyright notice in the Description page of Project Settings.


#include "MyOptionWidget.h"
#include "Components/TextBlock.h"
#include "Components/Slider.h"


void UMyOptionWidget::SetOptionState(float state)
{
	if (OptionState.Contains(state)) {
		if (IsValid(TextBlock_OptionState)) {
			TextBlock_OptionState->SetText(OptionState[state]);
		}
		if (IsValid(Slider_Option)) {
			Slider_Option->SetValue(state);
		}
	}
}

void UMyOptionWidget::ValueSwitchedHandler(float newValue)
{
	if (OptionState.Contains(newValue)) {
		if (IsValid(TextBlock_OptionState)) {
			TextBlock_OptionState->SetText(OptionState[newValue]);
		}
	}
}

void UMyOptionWidget::ValueChangedHandler()
{
	if (OnValueChanged.IsBound()) {
		OnValueChanged.Broadcast(static_cast<int32>(Slider_Option->GetValue()));
	}
}

void UMyOptionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (IsValid(Slider_Option)) {
		Slider_Option->OnValueChanged.AddDynamic(this, &UMyOptionWidget::ValueSwitchedHandler);
		Slider_Option->OnMouseCaptureEnd.AddDynamic(this, &UMyOptionWidget::ValueChangedHandler);
	}
}

void UMyOptionWidget::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	Slider_Option = nullptr;
	TextBlock_OptionState = nullptr;
}
