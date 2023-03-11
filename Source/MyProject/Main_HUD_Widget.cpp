// Fill out your copyright notice in the Description page of Project Settings.


#include "Main_HUD_Widget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Kismet/KismetTextLibrary.h"



void UMain_HUD_Widget::SetHealthStatus(float health)
{
	if (HealtheBar)
	{
		HealtheBar->SetPercent(health);
	}
}

void UMain_HUD_Widget::SetCurrentHealthText(int health)
{
	if (HealtheNumb)
	{
		HealtheNumb->SetText(UKismetTextLibrary::Conv_IntToText(health));
	}
}

void UMain_HUD_Widget::SetScores(int scores)
{
	if (IsValid(ScoresTextBlock))
	{
		ScoresTextBlock->SetText(UKismetTextLibrary::Conv_IntToText(scores));
	}
}

void UMain_HUD_Widget::SetCurGunAmmo(int CAmmo, int MaxAmmo)
{
	if (IsValid(CC_Ammo))
	{
		CC_Ammo->SetText(UKismetTextLibrary::Conv_IntToText(CAmmo));
	}
	if (IsValid(CC_MaxAmmo))
	{
		CC_MaxAmmo->SetText(UKismetTextLibrary::Conv_IntToText(MaxAmmo));
	}
}

void UMain_HUD_Widget::SetSecGunAmmo(int CAmmo, int MaxAmmo)
{
	if (IsValid(SC_Ammo))
	{
		SC_Ammo->SetText(UKismetTextLibrary::Conv_IntToText(CAmmo));
	}
	if (IsValid(SC_MaxAmmo))
	{
		SC_MaxAmmo->SetText(UKismetTextLibrary::Conv_IntToText(MaxAmmo));
	}
}
