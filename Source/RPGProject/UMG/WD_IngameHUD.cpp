#include "WD_IngameHUD.h"
#include "WD_Inventory.h"
#include "WD_ItemToolTip.h"
#include "WD_QuestPanel.h"
#include "WD_QuickSlot.h"
#include "WD_StatusPanel.h"
#include "RPGProject/Unit/Player/UnitPlayer.h"

UWD_IngameHUD* UWD_IngameHUD::CurrentWidget = nullptr;

void UWD_IngameHUD::onBorderClicked()
{
	AUnitPlayer* player = AUnitPlayer::CurrentPlayer;
	if (player)
		player->SetInputMode(true);
}

void UWD_IngameHUD::InitializeInventoryUI(int32 size)
{
	_inventory->InitSlots(size);
}

void UWD_IngameHUD::NativeConstruct()
{
	Super::NativeConstruct();
	CurrentWidget = this;

}

void UWD_IngameHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}