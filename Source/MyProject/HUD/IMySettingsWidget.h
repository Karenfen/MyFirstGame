#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "IMySettingsWidget.generated.h"

class UButton;
class UTextBlock;

UCLASS()
class MYPROJECT_API UIMySettingsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
	FText Name;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* TextBlock_Name;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* Button_Apply;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* Button_Default;

public:
	virtual void UpdateSettings();
	virtual void Cancel();

protected:
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	virtual void NativeConstruct() override;

	UFUNCTION()
	virtual void ApplySettings();
	UFUNCTION()
	virtual void SetDefaultSettings();

protected:
	class UGameUserSettings* UserSettings{ nullptr };
};
