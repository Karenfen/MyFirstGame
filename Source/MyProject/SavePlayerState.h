// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "GameStruct.h"
#include "SavePlayerState.generated.h"



UCLASS()
class MYPROJECT_API USavePlayerState : public USaveGame
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere)
	FPlayerTankState PlayerState;

public:
	USavePlayerState();
	void SavePlayerState(const FPlayerTankState& newState);
	FPlayerTankState GetPlayerState() const;
	bool IsEmpty() const;

protected:
	friend class AMainMenuLevelScriptActor;
	friend class AMapLoader;
};
