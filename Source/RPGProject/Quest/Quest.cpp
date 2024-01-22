#include "Quest.h"

#include "QuestManager.h"
#include "QuestTask.h"
#include "RPGProject/Global/Defines.h"
#include "RPGProject/UMG/WD_QuestTask.h"


void UQuest::Initialize(const FQuestData questData)
{
	_data = questData;

	_data.Status = EQUEST_STATUS::INPROGRESS;

	//1. _data의 Clear 조건에 따라, QuestManager와 연결해야한다.

	for(auto condition : _data.ClearConditions)
	{
		QuestTask* task = new QuestTask(condition,this);
		_questTasks.Add(task);

		QuestManager::GetInstance()->RegisterTask(condition.type, condition.Value, task);
	}
}

void UQuest::UpdateStatus()
{
	for (auto task  : _questTasks)
	{
		if(!task->Completed)
			return;
	}

	_data.Status = EQUEST_STATUS::COMPLETE;
	Finish();
}

void UQuest::Finish()
{
	for (auto task  : _questTasks)
	{
		QuestManager::GetInstance()->ClearTask(task->GetData().type, task->GetData().Value);
	}

	OnFinish.Broadcast();
}
