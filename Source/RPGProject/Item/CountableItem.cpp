#include "CountableItem.h"

#include "../Global/ItemManager.h"
#include "ItemSlot.h"

void CountableItem::Clear()
{
	Item::Clear();

	_amount = 0;
	SetData(ItemManager::GetEmptyCountItemData());

	if(_itemSlot)
		_itemSlot->SetItem(nullptr);


}

void CountableItem::Merge(CountableItem* countableItem)
{
	


}

void CountableItem::SetData(const FItemData* data)
{
	*(FCountItemData*) _itemData = *(FCountItemData*) data;
	if(_itemData->IconAsset.IsPending())
		_itemData->IconAsset.LoadSynchronous();

	UpdateSlot();
}

void CountableItem::SetAmount(short newAmount)
{
	_amount = newAmount;

	if(_amount <= 0)
		Clear();

	UpdateSlot();

}

void CountableItem::UpdateSlot()
{
	if (_itemSlot)
	{
		_itemSlot->UpdateSlot(GetItemData()->IconAsset.Get(), _amount);
	}
}
