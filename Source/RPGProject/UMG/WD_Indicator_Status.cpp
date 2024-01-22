#include "WD_Indicator_Status.h"
#include "EngineMinimal.h"

#include <Components/ProgressBar.h>
#include <Components/TextBlock.h>

#include "Components/HorizontalBox.h"
#include "RPGProject/Buff/Buff.h"
#include "RPGProject/DataBase/UnitDB.h"
#include "RPGProject/Global/DictionaryManager.h"
#include "RPGProject/Unit/UnitModelComponent.h"
#include "RPGProject/Unit/Player/PlayerModelComponent.h"
#include "RPGProject/Unit/Player/UnitPlayer.h"

int32 UWD_Indicator_Status::buffCount = 0;

void UWD_Indicator_Status::RegisterUI(UPlayerModelComponent* model)
{
	FPlayerData* data = model->GetData();

	model->OnUpdateHP.AddUObject(this, &UWD_Indicator_Status::UpdateHPBar);
	model->OnUpdateMP.AddUObject(this, &UWD_Indicator_Status::UpdateMPBar);
	model->OnUpdateEXP.AddUObject(this, &UWD_Indicator_Status::UpdateEXPBar);
	model->OnUpdateName.AddUObject(this, &UWD_Indicator_Status::UpdateName);
	model->OnUpdateLevel.AddUObject(this, &UWD_Indicator_Status::UpdateLevel);
	model->OnRegisterBuff.AddUObject(this, &UWD_Indicator_Status::RegisterBuff);

	UpdateHPBar(data->CurHP, model->GetData()->HP);
	UpdateMPBar(data->CurMP, model->GetData()->MP);
	UpdateEXPBar(data->CurExp, DictionaryManager::GetInstance()->GetRequiredExp(data->Level));
	UpdateLevel(data->Level);
	UpdateName(data->Name);

}

void UWD_Indicator_Status::UpdateHPBar(int32 CurrentHP, int32 MaxHP)
{
	_HPBar->SetPercent((float) CurrentHP / (float) MaxHP);
	FString str = FString::Printf(TEXT("%d/%d"), CurrentHP, MaxHP);
	_HPText->SetText(FText::FromString(str));
}

void UWD_Indicator_Status::UpdateMPBar(int32 currentMP, int32 maxMP)
{
	_MPBar->SetPercent((float) currentMP / (float) maxMP);
	FString str = FString::Printf(TEXT("%d/%d"), currentMP, maxMP);
	_MPText->SetText(FText::FromString(str));
}

void UWD_Indicator_Status::UpdateEXPBar(int32 currentEXP, int32 maxEXP)
{
	_EXPBar->SetPercent((float) currentEXP / (float) maxEXP);
	FString str = FString::Printf(TEXT("%d/%d"), currentEXP, maxEXP);
	_EXPText->SetText(FText::FromString(str));
}

void UWD_Indicator_Status::UpdateLevel(int32 currentLevel)
{
	FString str = FString::Printf(TEXT("Lv. %d"), currentLevel);
	_LevelText->SetText(FText::FromString(str));
}

void UWD_Indicator_Status::UpdateName(FText name)
{
	_NameText->SetText(name);
}

void UWD_Indicator_Status::RegisterBuff(UBuff* buff)
{
	FName text = FName(FString::Printf(TEXT("Buff Icon - %d"), buffCount));

	UWD_Buff* newBuffIcon = CreateWidget<UWD_Buff>(this, _buffClass.Get(), text);
	buffCount++;

	newBuffIcon->SetValue(buff->GetData().ID, buff->GetData().Duration, buff->GetData().IconAsset.Get());
	buff->OnEnd.AddUObject(newBuffIcon,&UWD_Buff::Delete);
	_buffs->AddChild(newBuffIcon);

}

void UWD_Indicator_Status::NativeConstruct()
{
	Super::NativeConstruct();

	_HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));
	_HPText = Cast<UTextBlock>(GetWidgetFromName(TEXT("HPText")));

	_MPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("MPBar")));
	_MPText = Cast<UTextBlock>(GetWidgetFromName(TEXT("MPText")));

	_EXPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("EXPBar")));
	_EXPText = Cast<UTextBlock>(GetWidgetFromName(TEXT("EXPText")));

	_NameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("NameText")));
	_LevelText = Cast<UTextBlock>(GetWidgetFromName(TEXT("LevelText")));


	//초기화 델리게이트 연결
	AUnitPlayer* _player = AUnitPlayer::CurrentPlayer;

	if (IsValid(_player))
	{
		if (_player->GetModel() != nullptr)
			_player->GetModel()->OnRegisterUI.AddUObject(this, &UWD_Indicator_Status::RegisterUI);
	}

}

void UWD_Indicator_Status::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}