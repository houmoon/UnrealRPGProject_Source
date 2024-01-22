#include "WD_CurrentQuest.h"

#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"

#include "WD_QuestTask.h"
#include "Components/Border.h"
#include "RPGProject/Quest/Quest.h"
#include "RPGProject/Quest/QuestTask.h"


void UWD_CurrentQuest::onFinished()
{
	_clearMark->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UWD_CurrentQuest::Initialize(UQuest* quest)
{
	_questName->SetText(quest->GetData().Name);
	_questDesc->SetText(quest->GetData().Description);

	for(int32 i = 0; i< quest->GetTask().Num();i++)
	{
		UWD_QuestTask* newTask = CreateWidget<UWD_QuestTask>(this, _taskClass.Get(), FName(quest->GetTask()[i]->GetName().ToString()));
		newTask->SetName((quest->GetTask())[i]->GetName());

		quest->GetTask()[i]->OnTaskUpdate.AddUObject(newTask, &UWD_QuestTask::UpdateTask);
		quest->GetTask()[i]->Update();

		_questElements->AddChild(newTask);
	}

	quest->OnFinish.AddUObject(this,&UWD_CurrentQuest::onFinished);
}

void UWD_CurrentQuest::NativeConstruct()
{
	Super::NativeConstruct();
}

void UWD_CurrentQuest::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}
