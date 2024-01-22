#pragma once

#include "CoreMinimal.h"
#include "RPGProject/DataBase/QuestDB.h"
#include "RPGProject/Enums/QuestEnums.h"

class UQuest;
//클리어 타입, ID, 현재수량, 목표수량, 완료 여부
DECLARE_MULTICAST_DELEGATE_FourParams(FDelegate_OnTaskUpdate,const int32, const int32,const int32, const bool);

class QuestTask
{
	private:
	UQuest* _quest = nullptr;
	FText _name;
	FQuestClearData _data;
public:
	bool Completed = false;

	public:
	QuestTask(FQuestClearData clearData, UQuest* quest);
	FQuestClearData& GetData() {return _data;}
	void AddCount(const int32);
	void Update(); 
	FText GetName() {return _name;}

	FDelegate_OnTaskUpdate OnTaskUpdate;
};
