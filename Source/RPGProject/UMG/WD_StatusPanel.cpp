#include "WD_StatusPanel.h"

#include "WD_EquipmentSlot.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Kismet/GameplayStatics.h"

#include "RPGProject/Global/DictionaryManager.h"
#include "RPGProject/Unit/Player/PlayerModelComponent.h"
#include "RPGProject/Unit/Player/UnitPlayer.h"
#include "RPGProject/Enums/ItemEnums.h"

void UWD_StatusPanel::RegisterUI(UPlayerModelComponent* model)
{
	initEquipSlot(_headSlot, EITEM_TYPE::EQUIPMENT_HELMET);
	initEquipSlot(_upperSlot, EITEM_TYPE::EQUIPMENT_UPPER);
	initEquipSlot(_lowerSlot, EITEM_TYPE::EQUIPMENT_LOWER);
	initEquipSlot(_shoesSlot, EITEM_TYPE::EQUIPMENT_SHOES);
	initEquipSlot(_weaponSlot, EITEM_TYPE::WEAPON);
}

void UWD_StatusPanel::UpdateStat(const FPlayerData& data)
{
	FString str;


	str = data.Name.ToString();
	_nameText->SetText(FText::FromString(str));


	str = FString::FromInt(data.Level);
	_levelText->SetText(FText::FromString(str));


	str = FString::Printf(TEXT("%d"), data.HP);
	_HPText->SetText(FText::FromString(str));


	str = FString::Printf(TEXT("%d"),data.MP);
	_MPText->SetText(FText::FromString(str));


	str = FString::Printf(TEXT("%d/%d"), data.CurExp, DictionaryManager::GetInstance()->GetRequiredExp(data.Level));
	_EXPText->SetText(FText::FromString(str));


	str = FString::FromInt(data.STR);
	_STRText->SetText(FText::FromString(str));


	str = FString::FromInt(data.INT);
	_INTText->SetText(FText::FromString(str));


	str = FString::FromInt(data.DEX);
	_DEXText->SetText(FText::FromString(str));


	str = FString::Printf(TEXT("%.2f"), data.ATK);
	_ATKText->SetText(FText::FromString(str));

	str = FString::Printf(TEXT("%.2f"), data.DEF);
	_DEFText->SetText(FText::FromString(str));

	str = FString::Printf(TEXT("%.2f"), data.HIT);
	_HITText->SetText(FText::FromString(str));

	str = FString::Printf(TEXT("%.2f"), data.DOG);
	_DOGText->SetText(FText::FromString(str));

	str = FString::Printf(TEXT("%.2f"),data.CRIT);
	_CRITText->SetText(FText::FromString(str));
	
}


void UWD_StatusPanel::initEquipSlot(UWD_EquipmentSlot* slot, EITEM_TYPE type)
{
	AUnitPlayer* _player = AUnitPlayer::CurrentPlayer;

	slot->SetType(type);
	slot->SetItemSlot((UItemSlot*)(_player->GetModel()->GetEquipSlot(type)));
}

void UWD_StatusPanel::NativeConstruct()
{
	Super::NativeConstruct();

	margin.Top = 4.0f;
	margin.Bottom = 4.0f;

	AUnitPlayer* _player = AUnitPlayer::CurrentPlayer;

	if(!_equipSlotClass)
		return;

	//델리게이트 연결
	if (IsValid(_player))
	{
		_playerModel = _player->GetModel();
		if (_playerModel != nullptr)
		{
			_playerModel->OnRegisterUI.AddUObject(this,&UWD_StatusPanel::RegisterUI);
			_playerModel->OnUpdateStat.AddUObject(this,&UWD_StatusPanel::UpdateStat);
		}
	}

}

void UWD_StatusPanel::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}