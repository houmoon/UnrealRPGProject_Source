#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "../Interfaces/IUsableItem.h"
#include "RPGProject/Enums/BuffEnums.h"

class EquipmentItem : public Item, public IUsableItem
{

public:
	EquipmentItem() { _itemData = new FEquipItemData; }
	virtual ~EquipmentItem() override { if(_itemData) delete _itemData; }

	public:
	virtual EquipmentItem* Clone() override { EquipmentItem* clone = new EquipmentItem; clone->SetData(GetItemData()); return clone; }
	virtual void Clear() override;
	virtual void SetData(const FItemData* data) override;

	virtual FEquipItemData* GetItemData() override { return (FEquipItemData*) _itemData; }

	virtual void OnUse() override;
	void OnEquip();
	void OnUnEquip();

	private:
	TArray<TPair<EBUFF_STAT, float>> _useCases;
};
