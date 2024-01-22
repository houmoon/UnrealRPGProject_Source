#include "Inventory.h"
#include "../../Global/ItemManager.h"
#include "../EquipmentItem.h"
#include "../UseItem.h"
#include <RPGProject/Gamemode/Gamemode_Ingame.h>

#include "Kismet/GameplayStatics.h"
#include "RPGProject/Global/Defines.h"
#include "RPGProject/UMG/WD_Inventory.h"

#include "RPGProject/Item/ItemSlot.h"
#include "RPGProject/UMG/WD_IngameHUD.h"
#include "RPGProject/Unit/Player/UnitPlayer.h"

UInventory::UInventory()
{
	_visibility = false;
	_world = nullptr;
}

void UInventory::Initialize(UWorld* world,int32 size)
{
	ItemManager::GetInstance();

	_world = world;
	_size = size;

	for (int32 i = 0; i < _size; i++)
	{
		UItemSlot* equipSlot = NewObject<UItemSlot>();
		equipSlot->SetType(EITEM_TYPE::EQUIPMENT);
		UItemSlot* useSlot = NewObject<UItemSlot>();
		useSlot->SetType(EITEM_TYPE::USE);
		UItemSlot* etcSlot = NewObject<UItemSlot>();
		etcSlot->SetType(EITEM_TYPE::ETC);

		_equipmentItems.Add(equipSlot);
		_useItems.Add(useSlot);
		_etcItems.Add(etcSlot);
	}

	// 게임모드로 부터 메인 HUD 가져오기
	UWD_IngameHUD* ingameHUD = UWD_IngameHUD::CurrentWidget;

	// InventoryWidget(UI) 초기화하기
	if(ingameHUD)
		ingameHUD->InitializeInventoryUI(_size);

}


UItemSlot* UInventory::GetItemSlot(int32 index, EITEM_TYPE type)
{
	if (index >= _size)
		return nullptr;

	if (Item::TypeisIncluding(type, EITEM_TYPE::EQUIPMENT))
		return _equipmentItems[index];

	if (Item::TypeisIncluding(type, EITEM_TYPE::USE))
		return _useItems[index];

	if (Item::TypeisIncluding(type, EITEM_TYPE::ETC))
		return _etcItems[index];

	return nullptr;
}

void UInventory::SetGold(const int32 gold)
{
	_gold = gold;
	if(_gold < 0)
		_gold = 0;

	if(_gold > 999999999)
		_gold = 999999999;

	UpdateGold();
}

void UInventory::AddItem(const int32 id)
{
	//아이템 데이터의 종류를 통해 새로운 인게임 아이템 객체를 만들어 할당.
	Item* item = ItemManager::GetInstance()->MakeItem(id);

	if(nullptr == item)
		return;

	AddItem(item);
}

void UInventory::AddItem(Item* item)
{
	if (nullptr == item)
		return;

	EquipmentItem* equipItem = dynamic_cast<EquipmentItem*>(item);

	if (nullptr != equipItem)
	{
		for(int16 i=0; i< _size; i++)
		{
			if(_equipmentItems[i]->GetItem() == nullptr)
			{
				_equipmentItems[i]->SetItem(equipItem);
				return;
			}
		}
		return;
	}

	CountableItem* etcItem = dynamic_cast<CountableItem*>(item);

	UseItem* useItem = dynamic_cast<UseItem*>(item);

	if (nullptr != etcItem)
	{
		if(nullptr != useItem)
		{
			for (int16 i = 0; i < _size; i++)
			{
				if (_useItems[i]->GetItem() == nullptr)
				{
					_useItems[i]->SetItem(useItem);
					return;
				}

				if(_useItems[i]->GetItem()->GetItemData()->ID == useItem->GetItemData()->ID)
				{
					CountableItem* pItem = (CountableItem*)(_useItems[i]->GetItem());
					uint8 count = pItem->GetAmount() + useItem->GetAmount();


					if(Item::TypeisIncluding(pItem->GetItemData()->Type, EITEM_TYPE::ETC_QUEST))
						OnAddItem.Broadcast(item->GetItemData()->ID);


					if(count > pItem->GetItemData()->MaxAmount)
					{
						useItem->SetAmount( useItem->GetAmount() - (pItem->GetItemData()->MaxAmount - pItem->GetAmount()) );
						pItem->SetAmount(pItem->GetItemData()->MaxAmount);
					}
					else
					{
						((CountableItem*) _useItems[i]->GetItem())->AddCount(useItem->GetAmount());
						return;
					}
				}
				
			}
			return;
		}

		for (int16 i = 0; i < _size; i++)
		{
			if (_etcItems[i]->GetItem() == nullptr)
			{
				_etcItems[i]->SetItem(etcItem);
				return;
			}

			if (_etcItems[i]->GetItem()->GetItemData()->ID == etcItem->GetItemData()->ID)
			{
				((CountableItem*) _etcItems[i]->GetItem())->AddCount(etcItem->GetAmount());
				return;
			}
		}
	}
}

void UInventory::DeleteItem(const int32 id)
{
}
