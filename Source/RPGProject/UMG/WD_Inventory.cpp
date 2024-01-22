#include "WD_Inventory.h"
#include "../UMG/WD_ItemToolTip.h"
#include "WD_InventoryBackpack.h"
#include "WD_ItemEventIndicator.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "RPGProject/Global/Defines.h"
#include "RPGProject/Item/Inventory/Inventory.h"

#include "RPGProject/Unit/Player/PlayerModelComponent.h"
#include "RPGProject/Unit/Player/UnitPlayer.h"

void UWD_Inventory::onHovered(UObject* data, bool isHovered)
{

}

void UWD_Inventory::UpdateGold(const int32 gold)
{
	if(_goldText)
		_goldText->SetText(FText::FromString(FString::FromInt(gold)));
}

void UWD_Inventory::InitSlots(int32 size)
{
	UInventory* inventory = AUnitPlayer::CurrentPlayer->GetModel()->GetInventory();

	if (inventory)
	{
		inventory->OnUpdateGold.AddUObject(this, &UWD_Inventory::UpdateGold);
	}


	_equipItemView->InitSlots(size, EITEM_TYPE::EQUIPMENT, _itemTooltip);
	_useItemView->InitSlots(size, EITEM_TYPE::USE, _itemTooltip);
	_etcItemView->InitSlots(size, EITEM_TYPE::ETC, _itemTooltip);

}

void UWD_Inventory::NativeConstruct()
{
	Super::NativeConstruct();

}