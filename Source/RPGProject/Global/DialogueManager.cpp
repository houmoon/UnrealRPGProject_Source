#include "DialogueManager.h"

#include "Defines.h"
#include "Engine/DataTable.h"

DialogueManager* DialogueManager::_instance = nullptr;

DialogueManager* DialogueManager::GetInstance()
{
	if(_instance == nullptr)
	{
		_instance = new DialogueManager();
	}

	return _instance;
}

DialogueManager::DialogueManager()
{

}

void DialogueManager::InitializeData_Dialogue(UDataTable* database)
{
	FString str;
	TArray<FDialogueData*> arrTableData;
	database->GetAllRows<FDialogueData>(str, arrTableData);

	TArray<FDialogueData> *newArray = nullptr;

	for(int i=0; i<arrTableData.Num(); i++)
	{
		//ID가 존재한다면 (0이 아니라면)
		if(arrTableData[i]->ID != 0)
		{
			//새로운 어레이를 만들어야함. Map에 연결된 어레이를 새로 정의.
			_dialogueData.Add(arrTableData[i]->ID, TArray<FDialogueData>());
			newArray = _dialogueData.Find(arrTableData[i]->ID);
			newArray->Add(*arrTableData[i]);
			
		}
		else
		{
			if(newArray != nullptr)
				newArray->Add(*arrTableData[i]);
		}
	}

	for(auto& tuple : _dialogueData)
	{
		for(int i=0; i< tuple.Value.Num();i++)
		{
			auto s = *(tuple.Value[i].Dialogue.ToString());
		}
	}
}

void DialogueManager::InitializeData_Selection(UDataTable* database)
{
	FString str;
	TArray<FSelectionData*> arrTableData;
	database->GetAllRows<FSelectionData>(str, arrTableData);

	TArray<FName> rowNames = database->GetRowNames();

	for (int i = 0; i < arrTableData.Num(); i++)
	{
		arrTableData[i]->ID = FCString::Atoi(*rowNames[i].ToString());
		_selectionData.Add(arrTableData[i]->ID, *arrTableData[i]);
	}
}

TArray<FDialogueData>* DialogueManager::GetDialogues(int32 id)
{
	TArray<FDialogueData> *dialogues = _dialogueData.Find(id);

	return dialogues;
}

const FSelectionData* DialogueManager::GetSelectionData(int32 id)
{
	FSelectionData* selection = _selectionData.Find(id);

	return selection;

}
