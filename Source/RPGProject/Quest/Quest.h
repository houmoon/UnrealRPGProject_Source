#pragma once

#include <CoreMinimal.h>

#include "QuestTask.h"
#include "RPGProject/DataBase/QuestDB.h"
#include "Quest.generated.h"

DECLARE_MULTICAST_DELEGATE(FDelegate_OnFinish);

UCLASS()
class RPGPROJECT_API UQuest : public UObject
{
	GENERATED_BODY()

private:
	TArray<QuestTask*> _questTasks;

	public:
	UFUNCTION(BlueprintCallable)
	void Initialize(const FQuestData questData);
	void UpdateStatus();
	void Finish();

	FDelegate_OnFinish OnFinish;

	const FQuestData GetData() { return _data; }
	TArray<QuestTask*> &GetTask() { return _questTasks; }

	private:
	FQuestData _data;
	



};
