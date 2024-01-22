#include "WD_QuestTask.h"

#include "Components/CheckBox.h"
#include "Components/TextBlock.h"
#include "RPGProject/Global/Defines.h"


void UWD_QuestTask::SetName(FText text)
{
	_taskName->SetText(text);
}

void UWD_QuestTask::UpdateTask(const int32 value, const int32 currentAmount,
                               const int32 amount, const bool isCleared)
{
	if(amount <= 1)
		_taskAmount->SetVisibility(ESlateVisibility::Hidden);
	else
		_taskAmount->SetVisibility(ESlateVisibility::HitTestInvisible);


	_taskAmount->SetText(FText::FromString(FString::Printf(TEXT("(%d/%d)"),currentAmount,amount)));

	if(isCleared)
		_checkBox->SetCheckedState(ECheckBoxState::Checked);
	else
		_checkBox->SetCheckedState(ECheckBoxState::Unchecked);
}

void UWD_QuestTask::NativeConstruct()
{
	Super::NativeConstruct();
}

void UWD_QuestTask::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}
