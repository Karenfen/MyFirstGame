// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenuWidget.h"
#include "Components/Button.h"
#include "../Player/TankPlayerController.h"


void UPauseMenuWidget::SetButtonClickeHandler(ATankPlayerController* handler)
{
	if (IsValid(Button_Resume))
	{
		Button_Resume->OnClicked.AddDynamic(handler, &ATankPlayerController::Unpause);
	}
	if (IsValid(Button_Quit))
	{
		Button_Quit->OnClicked.AddDynamic(handler, &ATankPlayerController::Quit);
	}
	if (IsValid(Button_Settings))
	{

	}
}