#include "WD_ItemToolTip.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "RPGProject/Item/Item.h"


void UWD_ItemToolTip::SetData(Item* item)
{
	if(item)
	{
		SetName(item->GetItemData()->Name);
		SetDescription(item->GetItemData()->Description);
		SetImage(item->GetItemData()->IconAsset.Get());
		SetTypeDescription(item->GetItemData()->Type);
	}

}

void UWD_ItemToolTip::SetName(FText name)
{
	_name->SetText(name);
}

void UWD_ItemToolTip::SetDescription(FText description)
{
	_description->SetText(description);
}

void UWD_ItemToolTip::SetTypeDescription(EITEM_TYPE type)
{
	FText text;
	

	switch(type)
	{
	case EITEM_TYPE::EQUIPMENT:
		FText::FindText(TEXT("ST_UI"), TEXT("UI_ITEM_EQUIP"), text);
		break;
	case EITEM_TYPE::EQUIPMENT_HELMET:
		FText::FindText(TEXT("ST_UI"), TEXT("UI_ITEM_EQUIP_HEAD"), text);
		break;
	case EITEM_TYPE::EQUIPMENT_UPPER:
		FText::FindText(TEXT("ST_UI"), TEXT("UI_ITEM_EQUIP_UPPER"), text);
		break;
	case EITEM_TYPE::EQUIPMENT_LOWER:
		FText::FindText(TEXT("ST_UI"), TEXT("UI_ITEM_EQUIP_LOWER"), text);
		break;
	case EITEM_TYPE::EQUIPMENT_SHOES:
		FText::FindText(TEXT("ST_UI"), TEXT("UI_ITEM_EQUIP_SHOES"), text);
		break;
	case EITEM_TYPE::WEAPON_SWORD:
		FText::FindText(TEXT("ST_UI"), TEXT("UI_WEAPON_SWORD"), text);
		break;
	case EITEM_TYPE::USE:
		FText::FindText(TEXT("ST_UI"), TEXT("UI_ITEM_USE"), text);
		break;
	case EITEM_TYPE::ETC:
		FText::FindText(TEXT("ST_UI"), TEXT("UI_ITEM_ETC"), text);
		break;
	case EITEM_TYPE::ETC_QUEST:
		FText::FindText(TEXT("ST_UI"), TEXT("UI_ITEM_ETC_QUEST"), text);
		break;
	case EITEM_TYPE::END:
		break;
	default: ;
	}

	_typedesc->SetText(text);

	//_typedesc->SetText(FText::FromName(Item::GetTypeString(type)));
}

void UWD_ItemToolTip::SetImage(UTexture2D* img)
{
	_image->SetBrushFromTexture(img);
}

void UWD_ItemToolTip::NativeConstruct()
{
	_name = Cast<UTextBlock>(GetWidgetFromName(L"Name"));
	_description = Cast<UTextBlock>(GetWidgetFromName(L"Description"));
	_image = Cast<UImage>(GetWidgetFromName(L"Image"));
	_typedesc = Cast<UTextBlock>(GetWidgetFromName(L"Type"));
}

void UWD_ItemToolTip::NativeTick(const FGeometry& geometry, float deltaTime)
{
	Super::NativeTick(geometry, deltaTime);
}


void UWD_ItemToolTip::SetToMousePosition()
{
	// 마우스 좌표 가져오기
	FVector2D MousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(this);

	UCanvasPanelSlot* slot = Cast<UCanvasPanelSlot>(Slot);

	if (slot)
		slot->SetPosition(MousePosition);
}

void UWD_ItemToolTip::SetToWidgetPosition(UWidget* widget)
{
	FGeometry ViewportGeometry = UWidgetLayoutLibrary::GetViewportWidgetGeometry(GetWorld());
	FGeometry widgetgeometry	= widget->GetCachedGeometry();

	const FVector2D& widgetPosToLocal = ViewportGeometry.AbsoluteToLocal(widgetgeometry.GetAbsolutePosition()) + (widgetgeometry.GetAbsoluteSize() * 2);

	UCanvasPanelSlot* slot = Cast<UCanvasPanelSlot>(Slot);

	if (slot)
		slot->SetPosition(widgetPosToLocal);
}
