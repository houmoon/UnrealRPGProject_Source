#pragma once

#include "CoreMinimal.h"
#include "RPGProject/DataBase/ItemDB.h"
#include "RPGProject/Enums/ItemEnums.h"


class CountableItem;
class UseItem;
class EquipmentItem;
class Item;

//아이템 DB 데이터를 저장하고, ID를 통해 아이템 정보를 불러오는 매니저
class ItemManager
{
	public: static ItemManager* GetInstance();
	private: static ItemManager* _instance;

	public:
	ItemManager();
	//아이템 DB 데이터를 형식에 타입에 맞게 설정하는 함수.
	void SetGameItemDataTable(EITEM_TYPE type, class UDataTable* dataTable);
	//ID로 아이템데이터를 찾는 포인터
	Item*	MakeItem(int32 id);

	const FItemData* const FindItem(int32 id);

	private:
	//빠른 타입 검색을 위한 데이터
	TMap<int32, EITEM_TYPE>			_typeDatas;

	//장비 아이템 데이터
	TMap<int32, FEquipItemData>		_equipmentDatas;
	//소비 아이템 데이터
	TMap<int32, FUseItemData>		_useDatas;
	//기타 아이템 데이터
	TMap<int32, FCountItemData>		_etcDatas;

	public:
	static FEquipItemData*	GetEmptyEquipItemData() { return &_emptyEquipItemData; }
	static FUseItemData*		GetEmptyUseItemData()	{ return &_emptyUseItemData; };
	static FCountItemData*	GetEmptyCountItemData() { return &_emptyCountItemData; };

	private:
	static FEquipItemData	_emptyEquipItemData;
	static FUseItemData		_emptyUseItemData;
	static FCountItemData	_emptyCountItemData;

};
