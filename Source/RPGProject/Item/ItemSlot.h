#pragma once

#include "CoreMinimal.h"
#include "EquipmentItem.h"

#include "UseItem.h"
#include "ItemSlot.generated.h"

class UseItem;
class CountableItem;
class EquipmentItem;

DECLARE_DELEGATE_TwoParams(FDelegate_OnUpdateSlot, UTexture2D*, uint8);


UCLASS()
class RPGPROJECT_API UItemSlot : public UObject
{
	GENERATED_BODY()

	public:
	virtual ~UItemSlot() {}

	protected:
	Item* _item = nullptr;
	EITEM_TYPE	_type;

	public:
	void	TryMoveItem(UItemSlot* to);

	private:
	void	trySwapItem(UItemSlot* to);
	bool 	tryAddItem(UItemSlot* to);
	bool	tryMergeItem(UItemSlot* To);

	public:
	virtual void	Use();
	void	SetType(EITEM_TYPE type) { _type = type; }
	virtual void	SetItem(Item* item);
	Item*	GetItem() { return _item; }

	public:
	UFUNCTION()
	void	UpdateSlot(UTexture2D* iconImg, uint8 amount) { OnUpdateSlot.Execute(iconImg, amount); }
	FDelegate_OnUpdateSlot OnUpdateSlot;
};