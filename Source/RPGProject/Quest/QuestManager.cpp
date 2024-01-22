#include "QuestManager.h"

#include "QuestTask.h"
#include "RPGProject/DataBase/QuestDB.h"
#include "RPGProject/Global/Defines.h"
#include "RPGProject/Item/Inventory/Inventory.h"
#include "RPGProject/Unit/UnitModelComponent.h"
#include "RPGProject/Unit/Player/PlayerModelComponent.h"
#include "RPGProject/Unit/Player/UnitPlayer.h"

QuestManager* QuestManager::_instance = nullptr;

QuestManager* QuestManager::GetInstance()
{
	if(_instance == nullptr)
	{
		_instance = new QuestManager();
	}

	return _instance;
}

QuestManager::QuestManager()
{
	
}

void QuestManager::InitDataTable(UDataTable* dataTable)
{
	_questData.Empty();
	_itemQuestData.Empty();
	_levelQuestData.Empty();

	FString str;
	TArray<FName> rowNames;

	rowNames = dataTable->GetRowNames();

	TArray<FQuestData*> questData;
	dataTable->GetAllRows<FQuestData>(str, questData);


	_tasks.Add(EQUEST_CLEAR_TYPE::KILL,TMap<int32,TArray<QuestTask*>>());
	_tasks.Add(EQUEST_CLEAR_TYPE::APPROACHAREA, TMap<int32, TArray<QuestTask*>>());
	_tasks.Add(EQUEST_CLEAR_TYPE::CHECKGOLD, TMap<int32, TArray<QuestTask*>>());
	_tasks.Add(EQUEST_CLEAR_TYPE::CHECKITEM, TMap<int32, TArray<QuestTask*>>());
	_tasks.Add(EQUEST_CLEAR_TYPE::INTERACTION, TMap<int32, TArray<QuestTask*>>());
	_tasks.Add(EQUEST_CLEAR_TYPE::TALK, TMap<int32, TArray<QuestTask*>>());
	_tasks.Add(EQUEST_CLEAR_TYPE::TRIGGER, TMap<int32, TArray<QuestTask*>>());

	for(int i=0; i<questData.Num(); i++)
	{
		questData[i]->ID = FCString::Atoi(*rowNames[i].ToString());
		_questData.Add(questData[i]->ID, *questData[i]);

		TArray<int32>* levelQuests;
		TArray<int32>* itemQuests;
		TArray<int32>* finishQuests;

		switch(questData[i]->EnableType)
		{
		case EQUEST_ENABLE_TYPE::LEVELUP:
			//레벨이 가리키는 어레이에 ID를 추가합니다. 없으면 어레이를 생성해서 ID를 삽입합니다.
			levelQuests = _levelQuestData.Find(questData[i]->Enable_Value);
			if(levelQuests)
				levelQuests->Add(questData[i]->ID);
			else
			{
				TArray<int32> newArray;
				newArray.Add(questData[i]->ID);
				_levelQuestData.Add(questData[i]->Enable_Value, newArray);
			}
			break;
		case EQUEST_ENABLE_TYPE::GETITEM:
			//아이템 ID가 가리키는 어레이에 ID를 추가합니다. 없으면 어레이를 생성해서 ID를 삽입합니다.
			itemQuests = _itemQuestData.Find(questData[i]->Enable_Value);
			if (itemQuests)
				itemQuests->Add(questData[i]->ID);
			else
			{
				TArray<int32> newArray;
				newArray.Add(questData[i]->ID);
				_itemQuestData.Add(questData[i]->Enable_Value, newArray);
			}
			break;
		case EQUEST_ENABLE_TYPE::FINISHQUEST:
			finishQuests = _finishQuestData.Find(questData[i]->Enable_Value);
			if (finishQuests)
				finishQuests->Add(questData[i]->ID);
			else
			{
				TArray<int32> newArray;
				newArray.Add(questData[i]->ID);
				_finishQuestData.Add(questData[i]->Enable_Value, newArray);
			}
			break;
		}
	}

}

void QuestManager::Subscribe(UPlayerModelComponent* playerModel)
{
	playerModel->OnUpdateLevel.AddRaw(this,&QuestManager::onUpdateLevel);
	playerModel->OnFinishedQuest.AddRaw(this,&QuestManager::onFinishQuest);
}

void QuestManager::Subscribe(UInventory* inventory)
{
	inventory->OnAddItem.AddRaw(this,&QuestManager::onAddItem);
}

FQuestData* const QuestManager::FindQuest(const int32 id)
{
	FQuestData* questData = _questData.Find(id);
	if(questData)
		return questData;
	else
	{
		return nullptr;
	}
}

void QuestManager::onUpdateLevel(const int32 currentLevel)
{
	UPlayerModelComponent* playerModel = AUnitPlayer::CurrentPlayer->GetModel();

	TArray<int32>* levelQuestData = _levelQuestData.Find(currentLevel);
	if(!levelQuestData)
		return;

	if(levelQuestData->Num() > 0)
	{
		for(int i=0; i<levelQuestData->Num(); i++)
		{
			playerModel->EnableQuest((*levelQuestData)[i]);
		}
	}
}

void QuestManager::onAddItem(const int32 id)
{
	UPlayerModelComponent* playerModel = AUnitPlayer::CurrentPlayer->GetModel();

	TArray<int32>* itemQuestData = _itemQuestData.Find(id);
	if (!itemQuestData)
		return;

	for (int i = 0; i < itemQuestData->Num(); i++)
	{
		playerModel->EnableQuest((*itemQuestData)[i]);
	}
}

void QuestManager::onFinishQuest(const int32 id)
{
	UPlayerModelComponent* playerModel = AUnitPlayer::CurrentPlayer->GetModel();

	TArray<int32>* finishQuestData = _finishQuestData.Find(id);
	if(!finishQuestData)
		return;

	for (int i = 0; i < finishQuestData->Num(); i++)
	{
		playerModel->EnableQuest((*finishQuestData)[i]);
	}

}

void QuestManager::RegisterTask(EQUEST_CLEAR_TYPE type, const int32 ID, QuestTask* task)
{
	TArray<QuestTask*>* tasks;

	tasks = _tasks[type].Find(ID);
	if(tasks)
		tasks->Add(task);
	else
	{
		TArray<QuestTask*> newTaskArr;
		newTaskArr.Add(task);
		_tasks[type].Add(ID, newTaskArr);
	}
}

void QuestManager::ClearTask(EQUEST_CLEAR_TYPE type, const int32 ID)
{
	if(_tasks[type].Find(ID) != nullptr)
		_tasks[type].Remove(ID);
}

void QuestManager::OnMsgReceived(const EQUEST_CLEAR_TYPE type, const int32 ID)
{
	TArray<QuestTask*>* tasks = _tasks[type].Find(ID);
	if (tasks)
	{
		for (int32 i = 0; i < tasks->Num(); i++)
		{
			((*tasks)[i])->AddCount(1);
		}
	}
}
