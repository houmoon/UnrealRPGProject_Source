#include "WD_DialoguePanel.h"

#include "WD_SelectionButton.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/RichTextBlock.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "RPGProject/Global/Defines.h"
#include "RPGProject/Global/DialogueManager.h"
#include "RPGProject/Quest/QuestManager.h"
#include "RPGProject/Unit/Player/PlayerModelComponent.h"
#include "RPGProject/Unit/Player/UnitPlayer.h"

void UWD_DialoguePanel::EnQueueDialogue(int32 id)
{
	TArray<FDialogueData> *dialogues = DialogueManager::GetInstance()->GetDialogues(id);

	if(!dialogues)
		return;

	for(int i=0; i<dialogues->Num(); i++)
	{
		_dialogueQueue.Enqueue((*dialogues)[i]);
	}

	DequeueDialogue();
}


void UWD_DialoguePanel::acceptQuest()
{
	if(_questButton_Accept->GetVisibility() == ESlateVisibility::Hidden)
		return;

	AUnitPlayer* player = AUnitPlayer::CurrentPlayer;

	if(player)
		player->GetModel()->AcceptQuest(_questid);

	_questButton_Accept->SetVisibility(ESlateVisibility::Hidden);

	ExitDialogue();

}

void UWD_DialoguePanel::DequeueDialogue()
{
	if(_selectionBox->GetChildrenCount() > 0) //버티컬에 선택지가 들어가있다면 중지.
		return;

	if(_dialogueQueue.Dequeue(_currentDialogue))
	{
		AUnitPlayer* player = AUnitPlayer::CurrentPlayer;


		if(_currentDialogue.SelectionIDs.Num() <= 0)
			_selectionBox->SetVisibility(ESlateVisibility::Hidden);
		else
		{
			int buttonindex = 1;

			//버튼 초기화
			for (int i = 0; i < _currentDialogue.SelectionIDs.Num(); i++)
			{
				int32 id = _currentDialogue.SelectionIDs[i];

				const FSelectionData* data = DialogueManager::GetInstance()->GetSelectionData(id);

				if(data->QuestID != 0) //퀘스트가 있을 경우
				{
					if(data->CompleteQuest) //퀘스트 완료시 대화라면..
					{
						if (!(player->GetModel()->isQuestCompleted(data->QuestID)))
							continue;
					}
					else //퀘스트 수령 선택지 시
					{
						if (!(player->GetModel()->isQuestEnabled(data->QuestID)))
							continue;
					}
				}

				_selectionBox->AddChildToVerticalBox(_selectionButtons[i]);
				_selectionButtons[i]->Initialize(this, *data, buttonindex);
				_selectionButtons[i]->SetVisibility(ESlateVisibility::Visible);
				buttonindex++;
			}

			_selectionBox->SetVisibility(ESlateVisibility::Visible);
		}

		_questPanel->SetVisibility(ESlateVisibility::Hidden);

		//Initialize and Show Quest Panel
		if(_currentDialogue.QuestID != 0)
		{
			//퀘스트가 완료된 상태라면
			if (player->GetModel()->isQuestCompleted(_currentDialogue.QuestID))
				player->GetModel()->FinishQuest(_currentDialogue.QuestID);
			else
			{
				//퀘스트 패널을 띄움.
				FQuestData* const data = QuestManager::GetInstance()->FindQuest(_currentDialogue.QuestID);

				_questName->SetText(data->Name);
				_questDesc->SetText(data->Description);
				_questid = data->ID;
				_questPanel->SetVisibility(ESlateVisibility::HitTestInvisible);

				//수락, 거절 버튼을 추가.
				_selectionBox->AddChildToVerticalBox(_questButton_Accept);
				_selectionBox->AddChildToVerticalBox(_questButton_Reject);

				_selectionBox->SetVisibility(ESlateVisibility::Visible);
			}

		}

		if(_currentDialogue.Name.EqualTo(FText::GetEmpty()) == false)
			_nameText->SetText(_currentDialogue.Name);

		_dialogueText->SetText(_currentDialogue.Dialogue);

		SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		if(GetVisibility() == ESlateVisibility::Visible)
			ExitDialogue();
	}
}

void UWD_DialoguePanel::ExitDialogue()
{
	_selectionBox->SetVisibility(ESlateVisibility::Hidden);
	_nameText->SetText(FText::GetEmpty());
	_dialogueText->SetText(FText::GetEmpty());

	SetVisibility(ESlateVisibility::Hidden);

	AUnitPlayer* player = AUnitPlayer::CurrentPlayer;
	if (player)
	{
		player->OnEndDialogue();
	}

	ClearVerticalBox();
}

void UWD_DialoguePanel::ClearVerticalBox()
{
	TArray<UWidget*> childs = _selectionBox->GetAllChildren();

	//Initialize Selection Buttons
	for (int i = 0; i < childs.Num(); i++)
	{
		_selectionBox_cached->AddChildToVerticalBox(childs[i]);
	}
}

void UWD_DialoguePanel::RegisterUI()
{
}

void UWD_DialoguePanel::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	for (int32 i = 0; i < _selectionBox_cached->GetChildrenCount(); i++)
	{
		UWD_SelectionButton* button = Cast<UWD_SelectionButton>(_selectionBox_cached->GetChildAt(i));
		if (button)
			_selectionButtons.Add(button);
	}

	SetVisibility(ESlateVisibility::Hidden);

}

void UWD_DialoguePanel::NativeConstruct()
{
	Super::NativeConstruct();



}

void UWD_DialoguePanel::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}