#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPGProject/DataBase/DialogueDB.h"
#include "WD_DialoguePanel.generated.h"


class UWD_Button;
class UWD_CurrentQuest;
class UWD_SelectionButton;
class UPlayerModelComponent;
class UVerticalBox;
class UHorizontalBoxSlot;
class UTextBlock;
class URichTextBlock;

UCLASS()
class RPGPROJECT_API UWD_DialoguePanel : public UUserWidget
{
	GENERATED_BODY()

	public:
	TQueue<FDialogueData>	_dialogueQueue;
	FDialogueData			_currentDialogue;

	void EnQueueDialogue(int32 id);

	private:
	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* _nameText;

	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget))
	URichTextBlock* _dialogueText;

	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* _nextIndicator;

	// 3개의 선택지 버튼 추가 필요
	TArray<UWD_SelectionButton*> _selectionButtons;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = true, BindWidget))
	UVerticalBox* _selectionBox;

	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget))
	UVerticalBox* _selectionBox_cached;

	//퀘스트
	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget))
	UWidget* _questPanel;

	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* _questName;

	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* _questDesc;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = true, BindWidget))
	UWD_Button* _questButton_Accept;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = true, BindWidget))
	UWD_Button* _questButton_Reject;

	private:
	UFUNCTION(BlueprintCallable)
	void acceptQuest();

	int32 _questid = 0;

	public:
	void DequeueDialogue();
	UFUNCTION(BlueprintCallable)
	void ExitDialogue();
	void ClearVerticalBox();

	public:
	void RegisterUI();

	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

};
