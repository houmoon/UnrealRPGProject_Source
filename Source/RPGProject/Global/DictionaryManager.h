#pragma once

#include "CoreMinimal.h"
#include "RPGProject/DataBase/DictionaryDB.h"


class UDataTable;

//아이템 DB 데이터를 저장하고, ID를 통해 아이템 정보를 불러오는 매니저
class DictionaryManager
{
	public: static DictionaryManager* GetInstance();
	private: static DictionaryManager* _instance;

	public:
	DictionaryManager();


	private:
	int32 _levelupDatasSize;
	int32* _levelupDatas;

	TMap<int32, FAreaData> _areaData;

	public:
	int32 FindLevel(const int32 currentExp);
	int32 GetRequiredExp(const int32 currentLevel);
	FAreaData GetArea(const int32 ID);

	public:
	void InitializeData_Levelup(UDataTable* database);
	void InitializeData_Area(UDataTable* database);

};
