#pragma once

#include "CoreMinimal.h"
#include "WD_Button.h"
#include "Blueprint/UserWidget.h"
#include "RPGProject/DataBase/DialogueDB.h"
#include "WD_SelectionButton.generated.h"


class UWD_DialoguePanel;

UCLASS()
class RPGPROJECT_API UWD_SelectionButton : public UWD_Button
{
	GENERATED_BODY()

	private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true,BindWidget))
	UTextBlock* _keyTextBlock;
	UPROPERTY(EditAnywhere)
	FText _keyText;

	UWD_DialoguePanel* _dialoguePanel;
	int32 _id;

	public:
	virtual void BroadCast() override;
	void Initialize(UWD_DialoguePanel* dialoguePanel, const FSelectionData& selectionData, int32 index);

};
