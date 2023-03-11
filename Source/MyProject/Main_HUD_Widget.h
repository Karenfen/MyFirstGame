// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Main_HUD_Widget.generated.h"

class UTextBlock;
class UImage;

UCLASS()
class MYPROJECT_API UMain_HUD_Widget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetHealthStatus(float health);
	void SetCurrentHealthText(int health);
	void SetScores(int scores);
	void SetCurGunAmmo(int CAmmo, int MaxAmmo);
	void SetSecGunAmmo(int CAmmo, int MaxAmmo);

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UProgressBar* HealtheBar;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* HealtheNumb;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* ScoresTextBlock;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* CC_Icon;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* CC_Ammo;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* CC_MaxAmmo;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* SC_Icon;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* SC_Ammo;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* SC_MaxAmmo;
};
