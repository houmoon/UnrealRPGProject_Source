#include "BuffManager.h"

UBuffManager* UBuffManager::_instance = nullptr;

UBuffManager* UBuffManager::GetInstance()
{
	if (_instance == nullptr)
	{
		_instance = NewObject<UBuffManager>();
		_instance->AddToRoot();
	}

	return _instance;
}


UBuff* UBuffManager::GetBuff(int32 id)
{
	UBuff** buff = _buffs.Find(id);

	if(!buff)
		return nullptr;

	return *buff;
}

void UBuffManager::Initialize(UDataTable* database)
{
	FString str;
	TArray<FBuffData*> arrTableData;
	database->GetAllRows<FBuffData>(str, arrTableData);

	TArray<FName> rowNames = database->GetRowNames();

	for (int i = 0; i < arrTableData.Num(); i++)
	{
		arrTableData[i]->ID = FCString::Atoi(*rowNames[i].ToString());

		UBuff* buff = NewObject<UBuff>();
		buff->Initialize(*arrTableData[i]);

		_buffs.Add(arrTableData[i]->ID, buff);

	}

}
