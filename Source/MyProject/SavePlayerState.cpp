// Fill out your copyright notice in the Description page of Project Settings.


#include "SavePlayerState.h"

USavePlayerState::USavePlayerState()
{

}

void USavePlayerState::SavePlayerState(const FPlayerTankState& newState)
{
	PlayerState = newState;
}

FPlayerTankState USavePlayerState::GetPlayerState() const
{
	return PlayerState;
}

bool USavePlayerState::IsEmpty() const
{
	return PlayerState.IsEmpty();
}
