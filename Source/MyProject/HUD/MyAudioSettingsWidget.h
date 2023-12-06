#pragma once

#include "CoreMinimal.h"
#include "IMySettingsWidget.h"
#include "MyAudioSettingsWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UMyAudioSettingsWidget : public UIMySettingsWidget
{
	GENERATED_BODY()
	
public:
	virtual void UpdateSettings() override;

protected:
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	virtual void NativeConstruct() override;
	virtual void ApplySettings() override;
	virtual void SetDefaultSettings() override;
};
