// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathScreenWidget.h"
#include "Components/Button.h"
#include "../Player/TankPlayerController.h"
#include <Kismet/GameplayStatics.h>



void UDeathScreenWidget::SetButtonClickeHandler(ATankPlayerController* handler)
{
	if (IsValid(Button_Restart))
	{
		Button_Restart->OnClicked.AddDynamic(handler, &ATankPlayerController::Restart);
	}
	if (IsValid(Button_Quit))
	{
		Button_Quit->OnClicked.AddDynamic(handler, &ATankPlayerController::Quit);
	}
}