// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DeathScreenWidget.generated.h"

class UButton;


UCLASS()
class MYPROJECT_API UDeathScreenWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* Button_Restart;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* Button_Quit;

public:
	void SetButtonClickeHandler(class ATankPlayerController* handler);

};
