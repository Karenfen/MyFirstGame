// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class UButton;


UCLASS()
class MYPROJECT_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* Button_Start;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* Button_Quit;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* Button_Settings;

	void SetButtonClickeHandler(class AMainMenuLevelScriptActor* mainMenuLevel);

protected:
	UFUNCTION()
	void OpenSettings();
};
