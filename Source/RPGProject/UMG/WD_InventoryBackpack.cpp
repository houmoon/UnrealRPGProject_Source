#include "WD_InventoryBackpack.h"

#include "WD_InventorySlot.h"

#include "../UMG/WD_ItemToolTip.h"
#include <RPGProject/Item/EquipmentItem.h>
#include <RPGProject/Item/UseItem.h>

#include "Components/UniformGridPanel.h"
#include "Kismet/GameplayStatics.h"
#include "RPGProject/Global/Defines.h"
#include "RPGProject/Item/ItemSlot.h"
#include "RPGProject/Item/Inventory/Inventory.h"
#include "RPGProject/Unit/Player/PlayerModelComponent.h"
#include "RPGProject/Unit/Player/UnitPlayer.h"


void UWD_InventoryBackpack::InitSlots(int32 amount,EITEM_TYPE type,UWD_ItemToolTip* tooltip)
{
	if(!IsValid(_slotClass))
	{
		return;
	}

	UInventory* inventory = AUnitPlayer::CurrentPlayer->GetModel()->GetInventory();

	for(int i=0; i<amount; i++)
	{
		UWD_InventorySlot* newSlot = CreateWidget<UWD_InventorySlot>(this, _slotClass, *FString::Printf(TEXT("Slot (%d)"),i));

		int32 row = i * 0.1f;
		int32 column = i - (row * 10);

		newSlot->SetType(type);

		UItemSlot* item = inventory->GetItemSlot(i, type);
		newSlot->SetItemSlot(item);
		newSlot->SetTooltip(tooltip);

		_slotView->AddChildToUniformGrid(newSlot, row, column);
		_slots.Add(newSlot);
	}

	_size = amount;

}

void UWD_InventoryBackpack::NativeConstruct()
{
	Super::NativeConstruct();

	if(!IsValid(_slotClass))
	{
		return;
	}

	_slotView = Cast<UUniformGridPanel>(GetWidgetFromName(TEXT("SlotView")));
	if (!IsValid(_slotView))
	{
		return;
	}

}

void UWD_InventoryBackpack::NativeDestruct()
{
	Super::NativeDestruct();
}

