#include "CooltimeManager.h"

#include "Defines.h"
#include "Engine/DataTable.h"
#include "RPGProject/DataBase/BuffDB.h"
#include "RPGProject/DataBase/ItemDB.h"

CooltimeManager* CooltimeManager::_instance = nullptr;

CooltimeManager* CooltimeManager::GetInstance()
{
	if(_instance == nullptr)
	{
		_instance = new CooltimeManager();
	}

	return _instance;
}

CooltimeManager::CooltimeManager()
{

}

float CooltimeManager::GetCurrentCooltime(int32 ID)
{
	if (_cooltimes.Num() > 0)
	{
		float* pCooltime = _cooltimes.Find(ID);
			if(pCooltime == nullptr)
				return 0;
		return *pCooltime;
	}
		
	return 0;
}

void CooltimeManager::RegisterCooltime(int32 ID, float originalCooltime)
{
	float* cooltime = &_cooltimes[ID];
	if(!cooltime)
		return;
		
	*cooltime = originalCooltime;
	_cooltimeQueue.Add(cooltime);
}

void CooltimeManager::Initialize(UDataTable* database)
{
	FString str;

	TArray<FUseItemData*> arrTable;
	database->GetAllRows<FUseItemData>(str,arrTable);

	for(int i=0; i< arrTable.Num();i++)
	{
		_cooltimes.Add(arrTable[i]->ID, 0.f);
	}
	
}

void CooltimeManager::Initialize_Buff(UDataTable* database)
{
	FString str;

	TArray<FBuffData*> arrTable;
	database->GetAllRows<FBuffData>(str, arrTable);

	for (int i = 0; i < arrTable.Num(); i++)
	{
		_cooltimes.Add(arrTable[i]->ID, 0.f);
	}

}

void CooltimeManager::OnTick(float deltaTime)
{
	if(_cooltimeQueue.Num() > 0)
	{
		for (int i=0; i< _cooltimeQueue.Num();i++)
		{
			*(_cooltimeQueue[i]) -= deltaTime;
			if(*(_cooltimeQueue[i]) < 0)
				_cooltimeQueue.RemoveAt(i);
		}
	}
}
