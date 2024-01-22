#pragma once

#include "CoreMinimal.h"

#include "WD_DraggablePanel.h"
#include "WD_QuestPanel.generated.h"


class UWD_CurrentQuest;
class UQuest;
class UWD_QuestButton;
class UScrollBox;
class UWD_Button;
class UPlayerModelComponent;
class UVerticalBox;
class UTextBlock;

UCLASS()
class RPGPROJECT_API UWD_QuestPanel : public UWD_DraggablePanel
{
	GENERATED_BODY()
	private:
	static int32 questButtonIndex;
	static FMargin questButtonPadding;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	TSubclassOf<UWD_Button> _questButtonClass;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	TSubclassOf<UWD_QuestButton> _inProgressQuestButtonClass;


	UPROPERTY(EditAnywhere, meta = (BindWidget, AllowPrivateAccess = true))
	UScrollBox* _enabledGroup;

	UPROPERTY(EditAnywhere, meta = (BindWidget, AllowPrivateAccess = true))
	UScrollBox* _inprogressGroup;

	UPROPERTY(EditAnywhere, meta = (BindWidget, AllowPrivateAccess = true))
	UScrollBox* _completedGroup;

	//Right Quest Info Panel
	UPROPERTY(EditAnywhere, meta = (BindWidget, AllowPrivateAccess = true))
	UVerticalBox* _questInfo;

	UPROPERTY(EditAnywhere, meta = (BindWidget, AllowPrivateAccess = true))
	UVerticalBox* _questEnabledInfo;

	UPROPERTY(EditAnywhere, meta = (BindWidget, AllowPrivateAccess = true))
	UTextBlock* _questName;

	UPROPERTY(EditAnywhere, meta = (BindWidget, AllowPrivateAccess = true))
	UTextBlock* _questLevel;

	UPROPERTY(EditAnywhere, meta = (BindWidget, AllowPrivateAccess = true))
	UTextBlock* _questDesc;

private:
	TMap<int32, UWD_Button*> _enabledQuestButtons;
	TMap<int32, UWD_QuestButton*> _inprogressQuestButtons;

	public:
	void AddEnableQuestButton(int32 ID);
	UFUNCTION()
	void AddInprogressQuestButton(UQuest* quest);
	void CompleteQuest(int32 id);

	UFUNCTION()
	void OnClickedQuestButton(int32 ID);
	UFUNCTION()
	void OnClickedInProgressQuestButton(UWD_CurrentQuest* quest);

	UFUNCTION()
	void RegisterUI(UPlayerModelComponent* model);

	float debugTimer = 0.f;
	bool debugging = false;


	FTextFormat _levelLimit;


public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

};
