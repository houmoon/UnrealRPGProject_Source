#include "WD_ItemEvent.h"

#include "WD_ItemEventIndicator.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "RPGProject/Global/Defines.h"
#include "RPGProject/Item/CountableItem.h"
#include "RPGProject/Item/Item.h"


void UWD_ItemEvent::InitFromData(Item* item)
{
	//슬롯 데이터 갱신
	if(nullptr == item)
	{
		return;
	}

	CountableItem* countableItem = dynamic_cast<CountableItem*>(item);
	if (nullptr != countableItem)
	{
		// 아이템 수량 세팅
		_eventText->SetText(FText::FromString(FString::Printf(TEXT("'%s' %d개 획득."), *countableItem->GetItemData()->Name.ToString(), countableItem->GetAmount())));
		_eventText->SetVisibility(ESlateVisibility::Visible);

		PlayAnimation(_fadeOutAnim);
	}
	else
	{
		_eventText->SetText(FText::FromString(FString::Printf(TEXT("'%s' 획득."), *item->GetItemData()->Name.ToString())));
		_eventText->SetVisibility(ESlateVisibility::Visible);

		PlayAnimation(_fadeOutAnim);
	}

}

void UWD_ItemEvent::InitFromGoldData(const int32 gold)
{
	_eventText->SetText(FText::FromString(FString::Printf(TEXT("%d 골드 획득."), gold)));
	_eventText->SetVisibility(ESlateVisibility::Visible);

	PlayAnimation(_fadeOutAnim);

}

void UWD_ItemEvent::InitFromExpData(int32 exp)
{
	_eventText->SetText(FText::FromString(FString::Printf(TEXT("%d 경험치 획득."), exp)));
	_eventText->SetVisibility(ESlateVisibility::Visible);

	PlayAnimation(_fadeOutAnim);
}

void UWD_ItemEvent::onFadeOutFinished()
{
	_parent->DropSize();
	RemoveFromParent();
}

void UWD_ItemEvent::NativeConstruct()
{
	Super::NativeConstruct();

	_fadeOutEndDelegate.BindDynamic(this,&UWD_ItemEvent::onFadeOutFinished);

	BindToAnimationFinished(_fadeOutAnim,_fadeOutEndDelegate);

}

void UWD_ItemEvent::NativeTick(const FGeometry& geometry, float deltaTime)
{
	Super::NativeTick(geometry,deltaTime);

}
