#pragma once

#include "CoreMinimal.h"
#include "Quest.h"

#include "RPGProject/DataBase/QuestDB.h"

class UPlayerModelComponent;
class UInventory;
class UDataTable;

class QuestManager
{
	public: static QuestManager* GetInstance();
	private: static QuestManager* _instance;

	public:
	QuestManager();

	public:
	void InitDataTable(UDataTable* dataTable);
	void Subscribe(UPlayerModelComponent* playerModel);
	void Subscribe(UInventory* inventory);
	FQuestData* const FindQuest(const int32 id);


	private:
	TMap<int32,FQuestData> _questData;

	TMap<int32, TArray<int32>> _itemQuestData;
	TMap<int32, TArray<int32>> _levelQuestData;
	TMap<int32, TArray<int32>> _areaQuestData;
	TMap<int32, TArray<int32>> _finishQuestData;

	TMap<EQUEST_CLEAR_TYPE, TMap<int32, TArray<QuestTask*>>> _tasks;

	void onUpdateLevel(const int32 currentLevel);
	void onAddItem(const int32 id);
	void onFinishQuest(const int32 id);

public:
	void RegisterTask(EQUEST_CLEAR_TYPE type, const int32 ID, QuestTask* task);
	void ClearTask(EQUEST_CLEAR_TYPE type, const int32 ID);
	void OnMsgReceived(const EQUEST_CLEAR_TYPE type, const int32 ID);

};
