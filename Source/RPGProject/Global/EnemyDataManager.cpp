#include "EnemyDataManager.h"

#include "RPGProject/DataBase/UnitDB.h"

EnemyDataManager* EnemyDataManager::_instance = nullptr;

EnemyDataManager* EnemyDataManager::GetInstance()
{
	if(_instance == nullptr)
	{
		_instance = new EnemyDataManager();
	}

	return _instance;
}

void EnemyDataManager::SetDataTable(UDataTable* dataTable)
{
	_dataTable = dataTable;

	FString str;
	TArray<FName> rowNames;

	rowNames = _dataTable->GetRowNames();

	TArray<FEnemyData*> arrTableData;
	_dataTable->GetAllRows<FEnemyData>(str, arrTableData);
	for (int32 i = 0; i < arrTableData.Num(); i++)
	{
		arrTableData[i]->ID = FCString::Atoi(*rowNames[i].ToString());

		arrTableData[i]->CurHP = arrTableData[i]->HP;

		_enemyDatas.Add(arrTableData[i]->ID, *arrTableData[i]);
	}

}

const FEnemyData* const EnemyDataManager::GetEnemyData(const int32 ID)
{
	return  _enemyDatas.Find(ID);
}
