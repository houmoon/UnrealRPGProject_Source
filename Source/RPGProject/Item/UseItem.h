#pragma once

#include "CoreMinimal.h"
#include "CountableItem.h"
#include "../Interfaces/IItemUseCase.h"
#include "../Interfaces/IUsableItem.h"

class UseItem : public CountableItem, public IUsableItem
{
	public:
	UseItem() { _itemData = new FUseItemData; _itemData->Type = EITEM_TYPE::END; _amount = 1; }
	virtual ~UseItem() override { if (_itemData) delete _itemData; }

private:
	TArray<IItemUseCase*> useBehaviors;

	public:
	virtual UseItem* Clone() override { UseItem* clone = new UseItem; clone->SetData(GetItemData()); return clone; }
	virtual void Clear() override;
	virtual void OnUse() override;

	virtual void				SetData(const FItemData* data)	override;
	virtual FUseItemData* GetItemData()				override { return (FUseItemData*) _itemData; }

};
