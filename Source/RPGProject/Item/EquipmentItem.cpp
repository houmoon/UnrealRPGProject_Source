#include "EquipmentItem.h"

#include "EquipmentSlot.h"
#include "../Global/ItemManager.h"
#include "Kismet/GameplayStatics.h"
#include "RPGProject/Global/Defines.h"

#include "RPGProject/Unit/Player/PlayerModelComponent.h"
#include "RPGProject/Unit/Player/UnitPlayer.h"
#include "RPGProject/DataBase/ItemDB.h"

void EquipmentItem::Clear()
{
	Item::Clear();

	SetData(ItemManager::GetEmptyEquipItemData());
}

void EquipmentItem::SetData(const FItemData* data)
{
	FEquipItemData* equipItem = (FEquipItemData*) _itemData;
	*equipItem = *(FEquipItemData*) data;

	if(_itemData->IconAsset.IsPending())
		_itemData->IconAsset.LoadSynchronous();

	
	FText _description = _itemData->Description;
	_description = FText::Format(FText::FromString("{0}\n"), _description);

	FText enumKey;

	for (int32 i = 0; i < equipItem->UseCases.Num(); i++)
	{
		FText useCase;

		_useCases.Add({ equipItem->UseCases[i].useCase, equipItem->UseCases[i].amount });

		//사용 효과 만들기
		const UEnum* buffStatEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("EBUFF_STAT"));
		if(!buffStatEnum)
			continue;

		enumKey = buffStatEnum->GetDisplayNameTextByValue((int64) equipItem->UseCases[i].useCase);

		FText::FindText(TEXT("ST_ITEM"), enumKey.ToString(), useCase);
		useCase = FText::Format(useCase, equipItem->UseCases[i].amount);

		_description = FText::Format(FText::FromString("{0}\n{1}"), _description, useCase);
	}

	_itemData->Description = _description;

	UpdateSlot();
}

void EquipmentItem::OnUse()
{
	IUsableItem::OnUse();

	UEquipmentSlot* slot = UEquipmentSlot::GetEquipmentSlot(_itemData->Type);

	if(!slot)
		return;

	_itemSlot->TryMoveItem(slot);

}

void EquipmentItem::OnEquip()
{
	AUnitPlayer* player = AUnitPlayer::CurrentPlayer;
	if(!player)
		return;


	for(int i=0; i<_useCases.Num(); i++)
	{
		player->GetModel()->AddStat(_useCases[i].Key,_useCases[i].Value);
	}

}

void EquipmentItem::OnUnEquip()
{
	AUnitPlayer* player = AUnitPlayer::CurrentPlayer;
	if (!player)
		return;

	for (int i = 0; i < _useCases.Num(); i++)
	{
		player->GetModel()->AddStat(_useCases[i].Key, -_useCases[i].Value);
	}
}
