// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NoticeWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UNoticeWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* TextBlock_Massege;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* Button_Ok;

public:
	void SetMassege(const FText & massege);
	virtual bool Initialize() override;
};
