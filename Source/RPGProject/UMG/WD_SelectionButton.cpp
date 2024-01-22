#include "WD_SelectionButton.h"

#include <string>

#include "WD_DialoguePanel.h"
#include "RPGProject/Global/Defines.h"
#include "RPGProject/Quest/QuestManager.h"
#include "RPGProject/Unit/Player/PlayerModelComponent.h"
#include "RPGProject/Unit/Player/UnitPlayer.h"

void UWD_SelectionButton::BroadCast()
{
	if (GetVisibility() == ESlateVisibility::Hidden)
		return;

	if (_dialoguePanel)
	{
		_dialoguePanel->ClearVerticalBox();
		_dialoguePanel->EnQueueDialogue(_id);
		SetVisibility(ESlateVisibility::Hidden);
	}

}

void UWD_SelectionButton::Initialize(UWD_DialoguePanel* dialoguePanel, const FSelectionData& selectionData,int32 index)
{
	_dialoguePanel = dialoguePanel;

	_id = selectionData.DialogueID;

	if(selectionData.QuestID != 0)
	{
		FText format;

		FText::FindText(TEXT("ST_UI"), TEXT("UI_DIALOGUE_QUESTFORMAT"), format);
		SetText(FText::Format(format, QuestManager::GetInstance()->FindQuest(selectionData.QuestID)->Name));
	}
	else
	{
		SetText(selectionData.Dialogue);
	}
		

	_keyTextBlock->SetText(FText::FromString(FString::Printf(TEXT("%d"),index)));

	SetVisibility(ESlateVisibility::Visible);

}
