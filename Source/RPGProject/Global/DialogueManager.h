#pragma once

#include "CoreMinimal.h"
#include "RPGProject/DataBase/DialogueDB.h"
#include "RPGProject/DataBase/DictionaryDB.h"
class UDataTable;

class DialogueManager
{
	public: static DialogueManager* GetInstance();
	private: static DialogueManager* _instance;

	public:
	DialogueManager();


	private:
	TMap<int32, TArray<FDialogueData>> _dialogueData;
	TMap<int32, FSelectionData> _selectionData;

	public:
	void InitializeData_Dialogue(UDataTable* database);
	void InitializeData_Selection(UDataTable* database);

	TArray<FDialogueData>* GetDialogues(int32 id);
	const FSelectionData* GetSelectionData(int32 id);

};
