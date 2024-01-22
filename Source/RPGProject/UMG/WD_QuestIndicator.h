#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "WD_QuestIndicator.generated.h"


class UCanvasPanel;
class UPlayerModelComponent;
class UQuest;
class UVerticalBox;
class UWD_CurrentQuest;

UCLASS()
class RPGPROJECT_API UWD_QuestIndicator : public UUserWidget
{
	GENERATED_BODY()
	private:

	static FMargin _margin;

	UPROPERTY(EditAnywhere, meta = (BindWidget, AllowPrivateAccess = true))
	UCanvasPanel* _canvasPanel;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	TSubclassOf<UWD_CurrentQuest> _questClass;

	UPROPERTY(EditAnywhere, meta = (BindWidget, AllowPrivateAccess = true))
	UVerticalBox* _questGroup;

	TMap<int32, UWD_CurrentQuest*> _quests;

	public:
	UFUNCTION()
	void AddQuest(UQuest* quest);
	UFUNCTION()
	void CompleteQuest(int32 id);


	UFUNCTION()
	void RegisterUI(UPlayerModelComponent* model);

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

};
