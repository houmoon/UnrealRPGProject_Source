#pragma once

#include "CoreMinimal.h"
#include "WD_Button.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "RPGProject/Quest/Quest.h"
#include "WD_QuestButton.generated.h"

class UWD_CurrentQuest;

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_OnClickedQuest, UWD_CurrentQuest*);

UCLASS()
class RPGPROJECT_API UWD_QuestButton : public UWD_Button
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	TSubclassOf<UWD_CurrentQuest> _questClass;

	UWD_CurrentQuest* _currentQuest = nullptr;

public:
	FDelegate_OnClickedQuest OnClickedQuest;

	void Initialize(UQuest* quest);
	virtual void BroadCast() override { OnClickedQuest.Broadcast(_currentQuest); }
};
