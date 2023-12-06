#pragma once

#include "CoreMinimal.h"
#include "IMySettingsWidget.h"
#include "MyControllSettingsWidget.generated.h"


UCLASS()
class MYPROJECT_API UMyControllSettingsWidget : public UIMySettingsWidget
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
