#include "WD_QuestPanel.h"

#include "WD_Button.h"
#include "WD_CurrentQuest.h"
#include "WD_QuestButton.h"
#include "Components/ScrollBox.h"
#include "Components/ScrollBoxSlot.h"
#include "Components/VerticalBox.h"
#include "RPGProject/Quest/QuestManager.h"
#include "RPGProject/Unit/Player/PlayerModelComponent.h"
#include "RPGProject/Unit/Player/UnitPlayer.h"
#include "RPGProject/Enums/QuestEnums.h"

int32 UWD_QuestPanel::questButtonIndex = TNumericLimits<int32>::Min();
FMargin UWD_QuestPanel::questButtonPadding = FMargin(0.f,5.f);

void UWD_QuestPanel::AddEnableQuestButton(int32 ID)
{
	if (_questButtonClass)
	{
		questButtonIndex++;

		debugTimer = 0.f;
		debugging = true;

		FText questName = QuestManager::GetInstance()->FindQuest(ID)->Name;

		UWD_Button* newQuestButton = CreateWidget<UWD_Button>(this, _questButtonClass.Get(), FName(questName.ToString()));
		newQuestButton->SetVisibility(ESlateVisibility::Hidden);

		newQuestButton->SetValue(ID);
		newQuestButton->OnClickedButton_OneParam.AddDynamic(this,&UWD_QuestPanel::OnClickedQuestButton);

		_enabledQuestButtons.Add(ID,newQuestButton);

		_enabledGroup->AddChild(newQuestButton);
		UScrollBoxSlot* slot = Cast<UScrollBoxSlot>(newQuestButton->Slot);
		if (slot)
			slot->SetPadding(questButtonPadding);

		newQuestButton->SetText(questName);

		newQuestButton->SetVisibility(ESlateVisibility::Visible);
		
	}
}

void UWD_QuestPanel::AddInprogressQuestButton(UQuest* quest)
{
	auto questButton = _enabledQuestButtons.Find(quest->GetData().ID);

	if(questButton)
	{
		_enabledGroup->RemoveChild(*questButton);
		_enabledQuestButtons.Remove(quest->GetData().ID);
	}

	UWD_QuestButton* newButton = CreateWidget<UWD_QuestButton>(this,_inProgressQuestButtonClass.Get(),
		FName(FString::Printf(TEXT("Quest Button %d"),quest->GetData().ID)));

	_inprogressQuestButtons.Add(quest->GetData().ID,newButton);
	newButton->Initialize(quest);
	newButton->OnClickedQuest.AddUObject(this,&UWD_QuestPanel::OnClickedInProgressQuestButton);

	_inprogressGroup->AddChild(newButton);
	newButton->SetText(quest->GetData().Name);


}

void UWD_QuestPanel::CompleteQuest(int32 id)
{
	auto questButton = _inprogressQuestButtons.Find(id);
	if(!questButton)
		return;

	_questEnabledInfo->ClearChildren();
	_inprogressGroup->RemoveChild(*questButton);
}

void UWD_QuestPanel::OnClickedQuestButton(int32 ID)
{
	//UpdateQuestEnabledQuestButton
	FQuestData* quest = QuestManager::GetInstance()->FindQuest(ID);

	if(!quest)
		return;
	
	if(quest->EnableType == EQUEST_ENABLE_TYPE::LEVELUP)
		_questLevel->SetText(FText::Format(_questLevel->GetText(), quest->Enable_Value));
			
			//FromString(FString::Printf(TEXT("제한 레벨 : %d"), quest->Enable_Value)));
	else
		_questLevel->SetText(FText::GetEmpty());

	_questName->SetText(quest->Name);
	_questDesc->SetText(quest->Description);
	

	_questInfo->SetVisibility(ESlateVisibility::HitTestInvisible);
	

}

void UWD_QuestPanel::OnClickedInProgressQuestButton(UWD_CurrentQuest* quest)
{
	if(!_questEnabledInfo)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("questEnabledInfo is not valid."));
		return;
	}
		

	if (!quest)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("quest is not valid."));
		return;
	}
		

	_questEnabledInfo->ClearChildren();
	_questEnabledInfo->AddChild(quest);
	_questEnabledInfo->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UWD_QuestPanel::RegisterUI(UPlayerModelComponent* model)
{
	model->OnRegisterQuest.AddUObject(this,&UWD_QuestPanel::AddEnableQuestButton);
	model->OnAcceptQuest.AddUObject(this,&UWD_QuestPanel::AddInprogressQuestButton);
	model->OnFinishedQuest.AddUObject(this, &UWD_QuestPanel::CompleteQuest);
}


void UWD_QuestPanel::NativeConstruct()
{
	Super::NativeConstruct();

	UPlayerModelComponent* playerModel = AUnitPlayer::CurrentPlayer->GetModel();
	if(playerModel)
	{
		playerModel->OnRegisterUI.AddUObject(this,&UWD_QuestPanel::RegisterUI);
	}

}

void UWD_QuestPanel::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);


	if(debugging)
		debugTimer += InDeltaTime;
}