// Fill out your copyright notice in the Description page of Project Settings.


#include "SavePlayerState.h"

USavePlayerState::USavePlayerState()
{

}

void USavePlayerState::SavePlayerState(const FPlayerTankState& newState)
{
	PlayerState = newState;
	IsAvailable = true;
}

FPlayerTankState USavePlayerState::GetPlayerState() const
{
	if (IsAvailable)
	{
		return PlayerState;
	}

	return FPlayerTankState();
}
