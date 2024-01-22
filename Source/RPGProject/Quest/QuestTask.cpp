#include "QuestTask.h"

#include "Quest.h"
#include "RPGProject/Global/DictionaryManager.h"
#include "RPGProject/Global/EnemyDataManager.h"
#include "RPGProject/Global/ItemManager.h"

QuestTask::QuestTask(FQuestClearData clearData, UQuest* quest)
{
	_data = clearData;
	_quest = quest;

	FText format;

	//커스텀 설명이 비어있지 않다면
	if(!_data.CustomDescription.EqualTo(FText::GetEmpty()))
	{
		_name = _data.CustomDescription;
		return;
	}

	switch(clearData.type)
	{
		case EQUEST_CLEAR_TYPE::KILL:
			FText::FindText(TEXT("ST_Quest"), TEXT("QUEST_FORMAT_KILL"), format);
			_name = FText::Format(format, EnemyDataManager::GetInstance()->GetEnemyData(clearData.Value)->Name);
			break;
		case EQUEST_CLEAR_TYPE::TALK:
			FText::FindText(TEXT("ST_Quest"), TEXT("QUEST_FORMAT_TALK"), format);
			break;
		case EQUEST_CLEAR_TYPE::INTERACTION:
			FText::FindText(TEXT("ST_Quest"), TEXT("QUEST_FORMAT_INTERACTION"), format);
			break;
		case EQUEST_CLEAR_TYPE::APPROACHAREA:
			FText::FindText(TEXT("ST_Quest"), TEXT("QUEST_FORMAT_APPROACHAREA"), format);
			_name = FText::Format(format, DictionaryManager::GetInstance()->GetArea(clearData.Value).Name);
			break;
		case EQUEST_CLEAR_TYPE::CHECKITEM:
			FText::FindText(TEXT("ST_Quest"), TEXT("QUEST_FORMAT_CHECKITEM"), format);
			_name = FText::Format(format, ItemManager::GetInstance()->FindItem(clearData.Value)->Name);
			break;
		case EQUEST_CLEAR_TYPE::CHECKGOLD:
			FText::FindText(TEXT("ST_Quest"), TEXT("QUEST_FORMAT_CHECKGOLD"), format);
			break;
	}

	
}

void QuestTask::AddCount(const int32 count)
{
	_data.CurrentAmount += count;
	if(_data.CurrentAmount >= _data.Amount)
	{
		//완료
		_data.CurrentAmount = _data.Amount;
		Completed = true;
		_quest->UpdateStatus();
	}

	Update();

}

void QuestTask::Update()
{
	OnTaskUpdate.Broadcast(_data.Value, _data.CurrentAmount, _data.Amount, Completed);
}
