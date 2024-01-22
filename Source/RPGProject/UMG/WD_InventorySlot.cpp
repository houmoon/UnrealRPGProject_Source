#include "WD_InventorySlot.h"

#include "WD_DraggingItem.h"
#include "WD_ItemToolTip.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/PanelWidget.h"
#include "RPGProject/Global/CooltimeManager.h"
#include "RPGProject/Global/Defines.h"
#include "RPGProject/Item/CountableItem.h"
#include "RPGProject/Item/Item.h"
#include "RPGProject/Item/ItemSlot.h"
#include "RPGProject/Unit/Player/UnitPlayer.h"

UWD_ItemToolTip* UWD_InventorySlot::_tooltip = nullptr;

FReply UWD_InventorySlot::DetectDrag(const FPointerEvent& inMouseEvent, UWidget* widgetDetectingDrag, FKey dragKey)
{
	if (inMouseEvent.GetEffectingButton() == dragKey /*|| PointerEvent.IsTouchEvent()*/)
	{
		FEventReply Reply;
		Reply.NativeReply = FReply::Handled();

		if (widgetDetectingDrag)
		{
			TSharedPtr<SWidget> SlateWidgetDetectingDrag = widgetDetectingDrag->GetCachedWidget();
			if (SlateWidgetDetectingDrag.IsValid())
			{
				Reply.NativeReply = Reply.NativeReply.DetectDrag(SlateWidgetDetectingDrag.ToSharedRef(), dragKey);
				return Reply.NativeReply;
			}
		}
	}

	return FReply::Unhandled();
}

void UWD_InventorySlot::UpdateSlot(UTexture2D* iconImg, uint8 amount)
{
	if(nullptr == iconImg)
		_itemImg->SetVisibility(ESlateVisibility::Hidden);
	else
	{
		_itemImg->SetBrushFromTexture(iconImg);
		_itemImg->SetVisibility(ESlateVisibility::Visible);
	}

	if(0 == amount)
		_itemAmount->SetVisibility(ESlateVisibility::Hidden);
	else
	{
		_itemAmount->SetText(FText::FromString(FString::Printf(TEXT("%d"), amount)));
		_itemAmount->SetVisibility(ESlateVisibility::Visible);
	}
}

void UWD_InventorySlot::NativeConstruct()
{
	Super::NativeConstruct();

	_canvasSlot = Cast<UCanvasPanelSlot>(this);

	_itemImg = Cast<UImage>(GetWidgetFromName(TEXT("Img")));
	_itemAmount = Cast<UTextBlock>(GetWidgetFromName(TEXT("Amount")));
	_cooltime = Cast<UImage>(GetWidgetFromName(TEXT("Cooltime")));


	if(_cooltimeMT)
	{
		_cooltimeMTInstance = UMaterialInstanceDynamic::Create(_cooltimeMT, this);
		_cooltime->SetBrushFromMaterial(_cooltimeMTInstance);
		_cooltimeMTInstance->SetScalarParameterValue("Percent", 0.f);
	}

}

void UWD_InventorySlot::NativeTick(const FGeometry& geometry, float deltaTime)
{
	Super::NativeTick(geometry,deltaTime);
	if (_type == EITEM_TYPE::USE)
	{
		if(_item && _item->GetItem() && _cooltimeMTInstance)
		{
			float currentcooltime = CooltimeManager::GetInstance()->GetCurrentCooltime(_item->GetItem()->GetItemData()->ID);
			float cooltime = ((UseItem*) (_item->GetItem()))->GetItemData()->CoolTime;

			float percent = currentcooltime / cooltime;

			percent = 1.0f - percent;
			if(percent <= 0.f || percent >= 1.f)
				_cooltime->SetVisibility(ESlateVisibility::Hidden);
			else
			{
				_cooltime->SetVisibility(ESlateVisibility::Visible);
				_cooltimeMTInstance->SetScalarParameterValue("Percent", percent);
			}
		}
		else
			_cooltime->SetVisibility(ESlateVisibility::Hidden);
	}
}

FReply UWD_InventorySlot::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	_item->Use();

	return Super::NativeOnMouseButtonDoubleClick(InGeometry, InMouseEvent);
}

FReply UWD_InventorySlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	return DetectDrag(InMouseEvent, this, EKeys::LeftMouseButton);
}

void UWD_InventorySlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	if(nullptr == _item)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("UI가 슬롯을 가리키지 않음."));
		return;
	}
		

	if(nullptr == _item->GetItem())
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("UI가 가라키는 슬롯이 비어있음"));
		return;
	}

	UWD_DraggingItem* draggingItem = NewObject<UWD_DraggingItem>();
	this->SetVisibility(ESlateVisibility::HitTestInvisible);

	//인벤토리로부터 현재 인덱스의 정보를 가져오도록 지시.
	draggingItem->SetItemSlot(_item);
	draggingItem->DefaultDragVisual = _itemImg;

	//draggingItem->Pivot = EDragPivot::MouseDown;

	OutOperation = draggingItem;

}

bool UWD_InventorySlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	UWD_DraggingItem* draggingItem = Cast<UWD_DraggingItem>(InOperation);
	if(!draggingItem)
		return false;

	if (!draggingItem->GetItemSlot())
		return false;

	//현재 옮기고 있는 아이템의 슬롯 정보를 가져옴
	UItemSlot* _draggingItem = draggingItem->GetItemSlot();


	//옮기고 있는 아이템이 가리키는 슬롯이 비어있거나, 현재 슬롯이 존재하지 않는다면
	if(nullptr == _draggingItem->GetItem() || nullptr == _item)
		return false;

	//옮기고 있는 아이템을 현재 슬롯으로 옮기도록 시도.
	_draggingItem->TryMoveItem(_item);
	return false;

}

void UWD_InventorySlot::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);
	this->SetVisibility(ESlateVisibility::Visible);


}

void UWD_InventorySlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	if(_tooltip && _item && _item->GetItem())
	{
		_tooltip->SetData(_item->GetItem());

		//_tooltip->SetToWidgetPosition(this);
		_tooltip->SetVisibility(ESlateVisibility::HitTestInvisible);
	}

}

void UWD_InventorySlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	if (_tooltip)
	{
		_tooltip->SetVisibility(ESlateVisibility::Hidden);
	}
}