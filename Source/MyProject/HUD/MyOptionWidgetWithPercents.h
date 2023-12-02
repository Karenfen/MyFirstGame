// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyOptionWidget.h"
#include "MyOptionWidgetWithPercents.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UMyOptionWidgetWithPercents : public UMyOptionWidget
{
	GENERATED_BODY()

	DECLARE_EVENT_OneParam(UMyOptionWidgetWithPercents, FOnOptionPercentsChangedEvent, float);

public:
	// вызывается когда нужно изменить настройку
	FOnOptionPercentsChangedEvent OnPercentsChanged;

	UPROPERTY(BlueprintReadWrite)
	float minValue;

	UPROPERTY(BlueprintReadWrite)
	float maxValue;

public:
	virtual void SetOptionState(float state) override;
	virtual void ValueSwitchedHandler(float newValue) override;
	virtual void ValueChangedHandler() override;
	UFUNCTION()
	void SetRange(float min, float max);

protected:
	virtual void NativeConstruct() override;

private:
	float onePercent {1.0f};
};
