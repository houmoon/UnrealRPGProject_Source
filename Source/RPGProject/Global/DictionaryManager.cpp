#include "DictionaryManager.h"

#include "Engine/DataTable.h"
#include "RPGProject/DataBase/DictionaryDB.h"

DictionaryManager* DictionaryManager::_instance = nullptr;

DictionaryManager* DictionaryManager::GetInstance()
{
	if(_instance == nullptr)
	{
		_instance = new DictionaryManager();
	}

	return _instance;
}

DictionaryManager::DictionaryManager()
{

}

int32 DictionaryManager::FindLevel(int32 currentExp)
{

	int32 left = 0;
	int32 mid = 0;
	int32 right = _levelupDatasSize - 1;

	while (true)
	{
		mid = (int32)((left + right) * 0.5f);

		if (currentExp == _levelupDatas[mid + 1])
			return mid + 2;

		if (currentExp == _levelupDatas[mid])
			return mid + 1;

		if (currentExp > _levelupDatas[mid + 1])
			left = mid;
		else if (currentExp < _levelupDatas[mid])
			right = mid;
		else
			return mid + 1;

		if (mid == (int32) ((left + right) * 0.5f))
			return mid + 1;

	}
}

int32 DictionaryManager::GetRequiredExp(int32 currentLevel)
{
	if(currentLevel <= 0)
		return 0;

	if(currentLevel > _levelupDatasSize)
		return  _levelupDatas[_levelupDatasSize - 1];

	return _levelupDatas[currentLevel - 1];
}

FAreaData DictionaryManager::GetArea(const int32 ID)
{
	FAreaData* area = _areaData.Find(ID);
	if(area)
		return *area;
	else
		return FAreaData();

}

void DictionaryManager::InitializeData_Levelup(UDataTable* database)
{
	FString str;
	TArray<FLevelUpData*> arrTableData;
	database->GetAllRows<FLevelUpData>(str, arrTableData);

	_levelupDatasSize = arrTableData.Num();
	_levelupDatas = new int[arrTableData.Num()];


	for(int i=0; i< _levelupDatasSize; i++)
	{
		_levelupDatas[i] = (arrTableData[i]->NextExp);
	}
}

void DictionaryManager::InitializeData_Area(UDataTable* database)
{
	FString str;
	TArray<FAreaData*> arrTableData;
	TArray<FName> rownames = database->GetRowNames();

	database->GetAllRows<FAreaData>(str, arrTableData);

	for (int i = 0; i < arrTableData.Num(); i++)
	{
		arrTableData[i]->ID = FCString::Atoi(*rownames[i].ToString());
		_areaData.Add(arrTableData[i]->ID, *arrTableData[i]);
	}

}
