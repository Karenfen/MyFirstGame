#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MySettingsMenuWidget.generated.h"

class UButton;
class UWidgetSwitcher;
class UMyGraphicSettingsWidget;
class UMyAudioSettingsWidget;
class UMyControllSettingsWidget;



UCLASS()
class MYPROJECT_API UMySettingsMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* Button_Graphic;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* Button_Controll;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* Button_Audio;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* Button_Close;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UWidgetSwitcher* WidgetSwitcher;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UMyGraphicSettingsWidget* BP_GraphicsSettingsWidget;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UMyControllSettingsWidget* BP_ControllSettingsWidget;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UMyAudioSettingsWidget* BP_AudioSettingsWidget;

public:
	UFUNCTION()
	void Open();

protected:
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	virtual void NativeConstruct() override;

	UFUNCTION()
	void SetActiveGraphicsPanel();
	UFUNCTION()
	void SetActiveControllPanel();
	UFUNCTION()
	void SetActiveAudioPanel();
	UFUNCTION()
	void CloseMenu();
};

