
#include "MyOptionWidgetWithPercents.h"
#include "Components/TextBlock.h"
#include "Components/Slider.h"

void UMyOptionWidgetWithPercents::SetOptionState(float state)
{
	float newValue = state;

	if (IsValid(Slider_Option)) {
		if (newValue < minValue) {
			newValue = minValue;
		}
		else if (newValue > maxValue) {
			newValue = maxValue;
		}
		
		int32 valueInPercent = FMath::RoundToFloat((newValue - minValue) / onePercent);
		Slider_Option->SetValue(valueInPercent);
		ValueSwitchedHandler(valueInPercent);
	}
}

void UMyOptionWidgetWithPercents::ValueSwitchedHandler(float newValue)
{
	if (IsValid(TextBlock_OptionState)) {
		TextBlock_OptionState->SetText(FText::FromString(FString::FromInt(newValue)));
	}
}

void UMyOptionWidgetWithPercents::ValueChangedHandler()
{
	if (OnPercentsChanged.IsBound()) {
		float newValue = ((Slider_Option->GetValue()) * onePercent) + minValue;
		OnPercentsChanged.Broadcast(newValue);
		return;
	}

	Super::ValueChangedHandler();
}

void UMyOptionWidgetWithPercents::SetRange(float min, float max)
{
	if (min >= max) {
		return;
	}

	minValue = min;
	maxValue = max;
	onePercent = (max - min) / 100.0f;
}

void UMyOptionWidgetWithPercents::NativeConstruct()
{
	Super::NativeConstruct();

	if (IsValid(Slider_Option)) {
		Slider_Option->SetMinValue(0.0f);
		Slider_Option->SetMaxValue(100.0f);
		Slider_Option->SetStepSize(1.0f);
	}
}