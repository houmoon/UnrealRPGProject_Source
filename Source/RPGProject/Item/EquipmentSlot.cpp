#include "EquipmentSlot.h"

#include "RPGProject/Unit/Player/PlayerModelComponent.h"
#include "RPGProject/Unit/Player/UnitPlayer.h"

TMap<EITEM_TYPE, UEquipmentSlot*> UEquipmentSlot::_equipmentSlots = TMap<EITEM_TYPE, UEquipmentSlot*>();

void UEquipmentSlot::InitializeSlot()
{
	_equipmentSlots.Reset();

	AUnitPlayer* player = AUnitPlayer::CurrentPlayer;

	if(!player)
		return;

	_equipmentSlots.Add(EITEM_TYPE::EQUIPMENT_HELMET, player->GetModel()->GetEquipSlot(EITEM_TYPE::EQUIPMENT_HELMET));
	_equipmentSlots.Add(EITEM_TYPE::EQUIPMENT_UPPER, player->GetModel()->GetEquipSlot(EITEM_TYPE::EQUIPMENT_UPPER));
	_equipmentSlots.Add(EITEM_TYPE::EQUIPMENT_LOWER, player->GetModel()->GetEquipSlot(EITEM_TYPE::EQUIPMENT_LOWER));
	_equipmentSlots.Add(EITEM_TYPE::EQUIPMENT_SHOES, player->GetModel()->GetEquipSlot(EITEM_TYPE::EQUIPMENT_SHOES));
	_equipmentSlots.Add(EITEM_TYPE::WEAPON, player->GetModel()->GetEquipSlot(EITEM_TYPE::WEAPON));
}

UEquipmentSlot* UEquipmentSlot::GetEquipmentSlot(EITEM_TYPE type)
{
	UEquipmentSlot** slot = _equipmentSlots.Find(type);

	if(!slot)
		return nullptr;

	return *slot;

}

void UEquipmentSlot::SetItem(Item* item)
{
	if (item != nullptr)
	{
		if (!item->isIncluding(_type))
			return;
	}

	if(_item != nullptr)
		((EquipmentItem*) _item)->OnUnEquip();

	_item = item;

	if (_item != nullptr)
	{
		((EquipmentItem*) _item)->OnEquip();
		_item->SetSlot(this);
		_item->UpdateSlot();
	}
	else
		UpdateSlot(nullptr, 0);

	AUnitPlayer* player = AUnitPlayer::CurrentPlayer;

	player->GetModel()->UpdateStat();

}
