#include "Item.h"

#include "ItemSlot.h"

bool Item::TypeisIncluding(EITEM_TYPE currentType, EITEM_TYPE type)
{
	return (((uint32) currentType & (uint32) type) == (uint32) type);
}

bool Item::isIncluding(EITEM_TYPE type)
{
	return (((uint32) GetItemData()->Type & (uint32) type) == (uint32) type);
}

void Item::UpdateSlot()
{
	if(_itemSlot)
	{
		_itemSlot->UpdateSlot(GetItemData()->IconAsset.Get(),0);
	}

}