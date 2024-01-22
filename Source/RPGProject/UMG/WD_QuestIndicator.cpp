#include "WD_QuestIndicator.h"

#include "WD_CurrentQuest.h"
#include "Components/CanvasPanel.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "RPGProject/Quest/Quest.h"
#include "RPGProject/Unit/Player/PlayerModelComponent.h"
#include "RPGProject/Unit/Player/UnitPlayer.h"

FMargin UWD_QuestIndicator::_margin = FMargin(0,5.f);

void UWD_QuestIndicator::AddQuest(UQuest* quest)
{
	UWD_CurrentQuest* newQuest = CreateWidget<UWD_CurrentQuest>(this,_questClass.Get(),FName(quest->GetData().Name.ToString()));
	newQuest->Initialize(quest);
	newQuest->SetVisibility(ESlateVisibility::Hidden);

	_quests.Add(quest->GetData().ID,newQuest);

	_questGroup->AddChild(newQuest);

	UVerticalBoxSlot* slot = Cast<UVerticalBoxSlot>(newQuest->Slot);
	if(slot)
	{
		slot->SetPadding(_margin);
	}

	newQuest->SetVisibility(ESlateVisibility::HitTestInvisible);

	_canvasPanel->SetVisibility(ESlateVisibility::HitTestInvisible);

}

void UWD_QuestIndicator::CompleteQuest(int32 id)
{
	auto quest = _quests.Find(id);

	if(!quest)
		return;

	_questGroup->RemoveChild(*quest);

	if(_questGroup->GetChildrenCount() <= 0)
	{
		_canvasPanel->SetVisibility(ESlateVisibility::Hidden);
	}

}

void UWD_QuestIndicator::RegisterUI(UPlayerModelComponent* model)
{
	model->OnAcceptQuest.AddUObject(this,&UWD_QuestIndicator::AddQuest);
	model->OnFinishedQuest.AddUObject(this,&UWD_QuestIndicator::CompleteQuest);
}

void UWD_QuestIndicator::NativeConstruct()
{
	Super::NativeConstruct();


	UPlayerModelComponent* playerModel = AUnitPlayer::CurrentPlayer->GetModel();
	if (playerModel)
	{
		playerModel->OnRegisterUI.AddUObject(this, &UWD_QuestIndicator::RegisterUI);
	}

	_canvasPanel->SetVisibility(ESlateVisibility::Hidden);

}

void UWD_QuestIndicator::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}
