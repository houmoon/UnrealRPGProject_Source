#include "WD_IngameMain.h"
#include "WD_IngameHUD.h"
#include "Components/Border.h"
#include "Components/WidgetSwitcher.h"
#include "RPGProject/Global/Defines.h"
#include "RPGProject/Unit/Player/UnitPlayer.h"

UWD_IngameMain* UWD_IngameMain::CurrentWidget = nullptr;


void UWD_IngameMain::SetWidgetIndex(int32 index)
{
	_widgetSwitcher->SetActiveWidgetIndex(index);
}

void UWD_IngameMain::NativeConstruct()
{
	Super::NativeConstruct();

	UWD_IngameMain::CurrentWidget = this;
	SetWidgetIndex(1);

}

void UWD_IngameMain::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry,InDeltaTime);

}
