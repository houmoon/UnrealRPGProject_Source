#include "ItemManager.h"

#include "Defines.h"
#include "../Item/EquipmentItem.h"
#include "../Item/UseItem.h"

FEquipItemData	ItemManager::_emptyEquipItemData = FEquipItemData();
FUseItemData	ItemManager::_emptyUseItemData = FUseItemData();
FCountItemData	ItemManager::_emptyCountItemData = FCountItemData();


ItemManager* ItemManager::_instance = nullptr;

ItemManager* ItemManager::GetInstance()
{
	if(_instance == nullptr)
	{
		_instance = new ItemManager();
	}

	return _instance;
}

ItemManager::ItemManager()
{
	_emptyEquipItemData.Type = EITEM_TYPE::END;
	_emptyCountItemData.Type = EITEM_TYPE::END;
	_emptyUseItemData.Type = EITEM_TYPE::END;
}

void ItemManager::SetGameItemDataTable(EITEM_TYPE type, UDataTable* dataTable)
{
	FString str;
	TArray<FName> rowNames;

	rowNames = dataTable->GetRowNames();

	switch (type)
	{
		case EITEM_TYPE::WEAPON:
		case EITEM_TYPE::EQUIPMENT:
		{
			TArray<FEquipItemData*> arrTableData_eqp;
			dataTable->GetAllRows<FEquipItemData>(str, arrTableData_eqp);
			for (int32 i = 0; i < arrTableData_eqp.Num(); i++)
			{
				arrTableData_eqp[i]->ID = FCString::Atoi(*rowNames[i].ToString());

				//ID에 따른 타입을 보관. (빠른 검색을 위해)
				_typeDatas.Add(arrTableData_eqp[i]->ID, arrTableData_eqp[i]->Type);
				_equipmentDatas.Add(arrTableData_eqp[i]->ID, *arrTableData_eqp[i]);
			}

			break;
		}
		case EITEM_TYPE::USE:
		{
			TArray<FUseItemData*> arrTableData_con;
			dataTable->GetAllRows<FUseItemData>(str, arrTableData_con);
			for (int32 i = 0; i < arrTableData_con.Num(); i++)
			{
				arrTableData_con[i]->ID = FCString::Atoi(*rowNames[i].ToString());

				_useDatas.Add(arrTableData_con[i]->ID, *arrTableData_con[i]);
				_typeDatas.Add(arrTableData_con[i]->ID, arrTableData_con[i]->Type);
			}
			break;
		}
		case EITEM_TYPE::ETC:
		{
			TArray<FCountItemData*> arrTableData_etc;
			dataTable->GetAllRows<FCountItemData>(str, arrTableData_etc);
			for (int32 i = 0; i < arrTableData_etc.Num(); i++)
			{
				arrTableData_etc[i]->ID = FCString::Atoi(*rowNames[i].ToString());

				_etcDatas.Add(arrTableData_etc[i]->ID, *arrTableData_etc[i]);
				_typeDatas.Add(arrTableData_etc[i]->ID, arrTableData_etc[i]->Type);
			}
			break;
		}

		default:
			break;
	}


}

Item* ItemManager::MakeItem(int32 id)
{
	EITEM_TYPE type = *(_typeDatas.Find(id));


	Item* item = nullptr;

	if (((int32) type & (int32) EITEM_TYPE::EQUIPMENT) == (int32) EITEM_TYPE::EQUIPMENT) //타입이 장비 범주에 들어가는지 검사
	{
		EquipmentItem* equipItem = new EquipmentItem();
		FEquipItemData* data = _equipmentDatas.Find(id);
		if(nullptr == data)
		{
			return nullptr;
		}

		equipItem->SetData(data);
		item = equipItem;
	}
		
	else if (((int32) type & (int32) EITEM_TYPE::USE) == (int32) EITEM_TYPE::USE) //타입이 소비 범주에 들어가는지 검사
	{
		UseItem* useitem = new UseItem();

		FUseItemData* data = _useDatas.Find(id);
		if (nullptr == data)
		{
			return nullptr;
		}

		useitem->SetData(data);
		item = useitem;
	}
	else if (((int32) type & (int32) EITEM_TYPE::ETC) == (int32) EITEM_TYPE::ETC) //타입이 소비 범주에 들어가는지 검사
	{
		CountableItem* countableitem = new CountableItem();

		FCountItemData* data = _etcDatas.Find(id);
		if (nullptr == data)
		{
			return nullptr;
		}

		countableitem->SetData(data);
		item = countableitem;
	}

	return item;
}

const FItemData* const ItemManager::FindItem(int32 id)
{
	EITEM_TYPE type = *(_typeDatas.Find(id));

	FItemData* item = nullptr;

	if (((int32) type & (int32) EITEM_TYPE::EQUIPMENT) == (int32) EITEM_TYPE::EQUIPMENT) //타입이 장비 범주에 들어가는지 검사
	{
		return &_equipmentDatas[id];
	}
	else if (((int32) type & (int32) EITEM_TYPE::USE) == (int32) EITEM_TYPE::USE) //타입이 소비 범주에 들어가는지 검사
	{
		return &_useDatas[id];
	}
	else if (((int32) type & (int32) EITEM_TYPE::ETC) == (int32) EITEM_TYPE::ETC) //타입이 소비 범주에 들어가는지 검사
	{
		return &_etcDatas[id];
	}

	return nullptr;
}
