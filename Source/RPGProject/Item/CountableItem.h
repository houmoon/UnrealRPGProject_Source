#pragma once

#include "CoreMinimal.h"
#include "Item.h"


class CountableItem : public Item
{

public:
	CountableItem() { _itemData = new FCountItemData; _itemData->Type = EITEM_TYPE::END; _amount = 1; }
	virtual ~CountableItem() override { if (_itemData) delete _itemData; }

	public:
	virtual CountableItem* Clone() override { CountableItem* clone = new CountableItem; clone->SetData(GetItemData()); return clone; }
	virtual void Clear() override;
	void AddCount(short amount) { SetAmount (_amount + amount); UpdateSlot(); }
	void Merge(CountableItem* countableItem);

	virtual void					SetData(Item* item) { SetAmount(((CountableItem*) item)->GetAmount()); SetData(item->GetItemData());  }
	virtual void					SetData(const FItemData* data)	override; 
	virtual FCountItemData*	GetItemData()				override { return (FCountItemData*) _itemData; }

	protected:
	short			_amount;

	public:
	short			GetAmount() {return _amount;}
	void			SetAmount(short newAmount);

	virtual void	UpdateSlot() override;

};
