#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WD_CurrentQuest.generated.h"

class UBorder;
class QuestTask;
class UWD_QuestTask;
class UQuest;
class UVerticalBox;
class UTextBlock;

UCLASS()
class RPGPROJECT_API UWD_CurrentQuest : public UUserWidget
{
	GENERATED_BODY()
	private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	TSubclassOf<UWD_QuestTask> _taskClass;

	UPROPERTY(EditAnywhere, meta = (BindWidget, AllowPrivateAccess = true))
	UTextBlock* _questName;
	UPROPERTY(EditAnywhere, meta = (BindWidget, AllowPrivateAccess = true))
	UTextBlock* _questDesc;
	UPROPERTY(EditAnywhere, meta = (BindWidget, AllowPrivateAccess = true))
	UVerticalBox* _questElements;
	UPROPERTY(EditAnywhere, meta = (BindWidget, AllowPrivateAccess = true))
	UBorder* _clearMark;

	UFUNCTION()
	void onFinished();

public:
	void Initialize(UQuest* quest);
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

};
