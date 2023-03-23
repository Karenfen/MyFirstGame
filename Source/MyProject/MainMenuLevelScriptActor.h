// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "MainMenuLevelScriptActor.generated.h"


class UButton;


UCLASS()
class MYPROJECT_API AMainMenuLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	class AMenuPlayerController* MenuController;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UMainMenuWidget* Menu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu")
	TSubclassOf<class UMainMenuWidget> MenuClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level loading params")
	FName LoadLevelName;

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void StartClicked();

	UFUNCTION()
	void QuitClicked();
};
