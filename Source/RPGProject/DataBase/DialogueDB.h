#pragma once

#include <Engine/DataTable.h>
#include "DialogueDB.generated.h"

UENUM()
enum class ESELECTION_TYPE : int8
{
	DIALOGUE,
	QUEST,
};


USTRUCT(Atomic, BlueprintType)
struct FDialogueData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int32	ID;

	UPROPERTY(EditAnywhere)
	FText	Name;

	UPROPERTY(EditAnywhere)
	FText	Dialogue;

	UPROPERTY(EditAnywhere)
	int32	QuestID;

	UPROPERTY(EditAnywhere)
	TArray<int32>	SelectionIDs;

};



USTRUCT(Atomic, BlueprintType)
struct FSelectionData : public FTableRowBase
{
	GENERATED_BODY()
	int32	ID;

	UPROPERTY(EditAnywhere)
	FText	Dialogue;

	UPROPERTY(EditAnywhere)
	int32 DialogueID;

	UPROPERTY(EditAnywhere)
	int32 QuestID;

	UPROPERTY(EditAnywhere)
	bool CompleteQuest = false;
};