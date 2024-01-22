#include "WD_QuestButton.h"
#include "WD_CurrentQuest.h"

void UWD_QuestButton::Initialize(UQuest* quest)
{
	_currentQuest = CreateWidget<UWD_CurrentQuest>(this, _questClass.Get(), FName(quest->GetData().Name.ToString()));
	_currentQuest->Initialize(quest);
}
