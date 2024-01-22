#include "WD_QuickSlot.h"

#include "WD_InventorySlot.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "RPGProject/Item/ItemSlot.h"
#include "RPGProject/Item/Inventory/QuickSlot.h"


void UWD_QuickSlot::InitSlots(UQuickSlot* quickSlot, int32 amount)
{
	if(!IsValid(_slotClass))
	{
		return;
	}

	_slotView->SetVisibility(ESlateVisibility::Hidden);

	FMargin margin(4.f, 0.f);

	for(int i=0; i<amount; i++)
	{
		UWD_InventorySlot* newSlot = CreateWidget<UWD_InventorySlot>(this, _slotClass, *FString::Printf(TEXT("Slot (%d)"),i));
		newSlot->SetType(EITEM_TYPE::USE);

		UItemSlot* item = quickSlot->GetItemSlot(i);
		item->OnUpdateSlot.Unbind();
		item->OnUpdateSlot.BindUObject(newSlot,&UWD_InventorySlot::UpdateSlot);

		newSlot->SetItemSlot(item);

		_slotView->AddChildToHorizontalBox(newSlot);
		UHorizontalBoxSlot* slot = Cast<UHorizontalBoxSlot>(newSlot->Slot);
		if(slot)
		{
			slot->SetPadding(margin);
		}

		_slots.Add(newSlot);
	}

	_slotView->SetVisibility(ESlateVisibility::Visible);

	_size = amount;

}

void UWD_QuickSlot::NativeConstruct()
{
	Super::NativeConstruct();

	if(!IsValid(_slotClass))
	{
		return;
	}

	_slotView = Cast<UHorizontalBox>(GetWidgetFromName(TEXT("SlotView")));
	if (!IsValid(_slotView))
	{
		return;
	}

}

void UWD_QuickSlot::NativeDestruct()
{
	Super::NativeDestruct();
}

