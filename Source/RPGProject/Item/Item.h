#pragma once

#include "CoreMinimal.h"
#include "RPGProject/DataBase/ItemDB.h"
#include "RPGProject/Enums/ItemEnums.h"


class UItemSlot;
DECLARE_DELEGATE_TwoParams(FDelegate_OnUpdateItemSlot, UTexture2D*, uint8);


class Item
{
public:
	Item() { _itemData = nullptr; }
	virtual ~Item() {}

	protected:
	FItemData* _itemData;
	UItemSlot* _itemSlot = nullptr;

	//Getter
	public:
	virtual FItemData* GetItemData()			{ return _itemData; }
	virtual Item* Clone() { Item* clone = new Item; clone->SetData(GetItemData()); return clone; }
	static bool TypeisIncluding(EITEM_TYPE currentType, EITEM_TYPE type);
	bool isIncluding(EITEM_TYPE type);


	//Setter
	public:
	void SetSlot(UItemSlot* itemSlot) { _itemSlot = itemSlot; }
	virtual void Clear() {}
	virtual void SetData(Item* item) { SetData(item->GetItemData()); }
	virtual void SetData(const FItemData* data) { *_itemData = *data; _itemData->IconAsset.LoadSynchronous(); }

	//Item Behaviors
	public:
	virtual void	UpdateSlot();

};
