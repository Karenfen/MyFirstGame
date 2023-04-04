// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SavePlayerState.h"
#include "MySaveGame.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UMySaveGame : public USavePlayerState
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	FName LevelName = "NONE";

public:
	void SaveLevel(const FName& newLevel) { LevelName = newLevel; };
	FName LoadLevel() const { return LevelName; };
	bool IsEmpty() const { return LevelName == "NONE"; };
};