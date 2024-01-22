#include "QuickSlot.h"

#include "Kismet/GameplayStatics.h"

#include "RPGProject/Enums/ItemEnums.h"
#include "RPGProject/Gamemode/Gamemode_Ingame.h"
#include "RPGProject/Global/Defines.h"
#include "RPGProject/Item/ItemSlot.h"
#include "RPGProject/UMG/WD_IngameHUD.h"
#include "RPGProject/UMG/WD_QuickSlot.h"
#include "RPGProject/Item/UseItem.h"


UQuickSlot::UQuickSlot()
{
	_visibility = false;
	_world = nullptr;
}

void UQuickSlot::Initialize(UWorld* world, int32 size)
{
	_world = world;
	_size = size;

	for (int32 i = 0; i < _size; i++)
	{
		UItemSlot* useSlot = NewObject<UItemSlot>();
		useSlot->SetType(EITEM_TYPE::USE);

		_itemSlots.Add(useSlot);
	}

	UWD_IngameMain* ingameMain = UWD_IngameMain::CurrentWidget;
	if (nullptr == ingameMain)
	{
		return;
	}

	// 게임모드로 부터 메인 HUD 가져오기
	UWD_IngameHUD* ingameHUD = ingameMain->GetHUD();

	_quickSlotUI = ingameHUD->GetQuickSlot();
	if (nullptr == _quickSlotUI)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("QuickSlot : UI 찾을 수 없음. 초기화 실패"));
		return;
	}

	_quickSlotUI->InitSlots(this,_size);
}

UItemSlot* UQuickSlot::GetItemSlot(int32 index)
{
	if(index >= _size)
		return nullptr;

	return _itemSlots[index];
}

void UQuickSlot::Use(int32 index)
{
	if (index >= _size)
		return;

	if(_itemSlots[index]->GetItem())
	{
		IUsableItem* useItem = dynamic_cast<IUsableItem*>(_itemSlots[index]->GetItem());
		if(useItem)
			useItem->OnUse();
	}
}

