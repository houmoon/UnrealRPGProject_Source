#include "ItemSlot.h"

#include "../Global/CooltimeManager.h"
#include "CountableItem.h"
#include "../Interfaces/IUsableItem.h"
#include "RPGProject/Global/Defines.h"

bool UItemSlot::tryAddItem(UItemSlot* To)
{
	if (nullptr == To->GetItem() && nullptr != this->GetItem())
	{
		To->SetItem(this->GetItem());
		this->SetItem(nullptr);

		return true;
	}

	return false;
}

void UItemSlot::TryMoveItem(UItemSlot* to)
{
	//아이템 타입이 슬롯 타입과 어울리지 않으면?
	if (false == this->GetItem()->isIncluding(_type))
		return;

	//1. 추가 (to 슬롯이 비어있을때, 즉 아이템 타입이 END 일때 추가 가능)
	if (tryAddItem(to))
		return;

	//2. 병합 (현재 슬롯의 아이템을 셀 수 있고, 둘의 종류가 같으면 병합 가능.)
	if (this->tryMergeItem(to))
		return;

	//3. 교체 (현재 슬롯의 아이템을 셀수 없거나, 다른 아이템이라면 교체 시도)
	trySwapItem(to);
}

void UItemSlot::trySwapItem(UItemSlot* To)
{
	Item* temp = GetItem();

	SetItem(To->GetItem());
	To->SetItem(temp);

}

bool UItemSlot::tryMergeItem(UItemSlot* To)
{
	if(nullptr == To || nullptr == To->GetItem())
		return false;

	CountableItem* countableItem_from	= dynamic_cast<CountableItem*>(GetItem());
	CountableItem* countableItem_to		= dynamic_cast<CountableItem*>(To->GetItem());

	if(nullptr == countableItem_from || nullptr == countableItem_to)
		return false;

	if(countableItem_from->GetItemData()->ID != countableItem_to->GetItemData()->ID)
		return false;

	//1. from의 Amount를 to의 Amount와 더한다
	uint8 addCount = countableItem_from->GetAmount() + countableItem_to->GetAmount();

	//addCount가 maxamount보다 크다면
	if(addCount > countableItem_to->GetItemData()->MaxAmount)
	{

		countableItem_to->SetAmount(countableItem_to->GetItemData()->MaxAmount);
		To->UpdateSlot(countableItem_to->GetItemData()->IconAsset.Get(), countableItem_to->GetAmount());

		countableItem_from->SetAmount(addCount - countableItem_to->GetItemData()->MaxAmount);
		UpdateSlot(countableItem_from->GetItemData()->IconAsset.Get(), countableItem_from->GetAmount());

		return true;
	}

	SetItem(nullptr);
	countableItem_to->SetAmount(addCount);
	To->UpdateSlot(countableItem_to->GetItemData()->IconAsset.Get(), countableItem_to->GetAmount());

	return true;

}

void UItemSlot::Use()
{
	IUsableItem* usableItem = dynamic_cast<IUsableItem*>(GetItem());

	if (usableItem)
		usableItem->OnUse();
}

void UItemSlot::SetItem(Item* item)
{
	if (item != nullptr)
	{
		if (!item->isIncluding(_type))
			return;
	}

	_item = item;

	if (_item != nullptr)
	{
		_item->SetSlot(this);
		_item->UpdateSlot();
	}
	else
		UpdateSlot(nullptr, 0);
}
