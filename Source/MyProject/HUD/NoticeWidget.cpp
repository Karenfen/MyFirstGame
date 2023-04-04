// Fill out your copyright notice in the Description page of Project Settings.


#include "NoticeWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UNoticeWidget::SetMassege(const FText & massege)
{
	if (IsValid(TextBlock_Massege))
	{
		TextBlock_Massege->SetText(massege);
	}
}

bool UNoticeWidget::Initialize()
{
	bool result = Super::Initialize();

	if (result)
	{
		if (IsValid(Button_Ok))
		{
			Button_Ok->OnClicked.AddDynamic(this, &UNoticeWidget::RemoveFromViewport);
		}
	}

	return result;
}