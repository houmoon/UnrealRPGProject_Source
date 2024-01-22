#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "WD_QuestTask.generated.h"

enum class EQUEST_CLEAR_TYPE : uint8;
class UCheckBox;
class UTextBlock;

UCLASS()
class RPGPROJECT_API UWD_QuestTask : public UUserWidget
{
	GENERATED_BODY()
	private:
	UPROPERTY(EditAnywhere, meta = (BindWidget, AllowPrivateAccess = true))
	UTextBlock* _taskName;

	UPROPERTY(EditAnywhere, meta = (BindWidget, AllowPrivateAccess = true))
	UTextBlock* _taskAmount;

	UPROPERTY(EditAnywhere, meta = (BindWidget, AllowPrivateAccess = true))
	UCheckBox* _checkBox;


public:
	void SetName(FText text);
	UFUNCTION()
	void UpdateTask(const int32 value, const int32 currentAmount, const int32 amount, const bool isCleared);
	

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

};
