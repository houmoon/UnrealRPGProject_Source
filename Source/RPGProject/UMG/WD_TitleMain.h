#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WD_TitleMain.generated.h"


class UWD_TitleHUD;

UCLASS()
class RPGPROJECT_API UWD_TitleMain : public UUserWidget
{
	GENERATED_BODY()

	private:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UWD_TitleHUD* _HUD;

	public:
	UWD_TitleHUD* GetHUD() { return _HUD;}
	
	public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

};
