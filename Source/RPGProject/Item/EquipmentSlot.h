#pragma once

#include "CoreMinimal.h"
#include "ItemSlot.h"
#include "EquipmentSlot.generated.h"

UCLASS()
class RPGPROJECT_API UEquipmentSlot : public UItemSlot
{
	GENERATED_BODY()

	private:
	static TMap<EITEM_TYPE, UEquipmentSlot*> _equipmentSlots;

	public:
	static void InitializeSlot();
	static UEquipmentSlot* GetEquipmentSlot(EITEM_TYPE);


	public:
	virtual ~UEquipmentSlot() {}

	public:
	virtual void SetItem(Item* item) override;

};