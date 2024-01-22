#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WD_TitleHUD.generated.h"


UCLASS()
class RPGPROJECT_API UWD_TitleHUD : public UUserWidget
{
	GENERATED_BODY()

	private:

	public:

	public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
};
