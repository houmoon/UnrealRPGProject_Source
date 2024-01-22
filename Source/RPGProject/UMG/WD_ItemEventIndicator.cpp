#include "WD_ItemEventIndicator.h"

#include "WD_ItemEvent.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/VerticalBox.h"
#include "Kismet/GameplayStatics.h"

#include "RPGProject/Unit/Player/PlayerModelComponent.h"
#include "RPGProject/Unit/Player/UnitPlayer.h"

int UWD_ItemEventIndicator::i = 0;
int UWD_ItemEventIndicator::j = 0;

void UWD_ItemEventIndicator::AddItem(Item* item)
{
	if (_itemEventClass)
	{
		i++;
		j++;

		FString str = FString::Printf(TEXT("Item Event (%d)"), i);

		UWD_ItemEvent* itemEvent = CreateWidget<UWD_ItemEvent>(this, _itemEventClass.Get(), FName(str));

		itemEvent->InitFromData(item);
		itemEvent->SetParent(this);

		_eventView->AddChildToVerticalBox(itemEvent);

		UCanvasPanelSlot* viewSlot = Cast<UCanvasPanelSlot>(_eventView->Slot);

		if(viewSlot)
		{
			viewSlot->SetSize(FVector2D(viewSlot->GetSize().X,30 * j));
		}
	}
	

}

void UWD_ItemEventIndicator::AddGold(int32 value)
{
	if (_itemEventClass && value > 0)
	{
		i++;
		j++;

		FString str = FString::Printf(TEXT("Gold Event (%d)"), i);

		UWD_ItemEvent* itemEvent = CreateWidget<UWD_ItemEvent>(this, _itemEventClass.Get(), FName(str));

		itemEvent->InitFromGoldData(value);
		itemEvent->SetParent(this);

		_eventView->AddChildToVerticalBox(itemEvent);

		UCanvasPanelSlot* viewSlot = Cast<UCanvasPanelSlot>(_eventView->Slot);

		if (viewSlot)
		{
			viewSlot->SetSize(FVector2D(viewSlot->GetSize().X, 30 * j));
		}
	}
}

void UWD_ItemEventIndicator::AddExp(int32 value)
{
	if (_itemEventClass && value > 0)
	{
		i++;
		j++;

		FString str = FString::Printf(TEXT("Exp Event (%d)"), i);

		UWD_ItemEvent* itemEvent = CreateWidget<UWD_ItemEvent>(this, _itemEventClass.Get(), FName(str));

		itemEvent->InitFromExpData(value);
		itemEvent->SetParent(this);

		_eventView->AddChildToVerticalBox(itemEvent);

		UCanvasPanelSlot* viewSlot = Cast<UCanvasPanelSlot>(_eventView->Slot);

		if (viewSlot)
		{
			viewSlot->SetSize(FVector2D(viewSlot->GetSize().X, 30 * j));
		}
	}
}

void UWD_ItemEventIndicator::DropSize()
{
	j--;
	UCanvasPanelSlot* viewSlot = Cast<UCanvasPanelSlot>(_eventView->Slot);

	if (viewSlot)
	{
		viewSlot->SetSize(FVector2D(viewSlot->GetSize().X, 30 * j));
	}
}

void UWD_ItemEventIndicator::NativeConstruct()
{
	Super::NativeConstruct();

	_eventView = Cast<UVerticalBox>(GetWidgetFromName(L"EventView"));

	UPlayerModelComponent* model = AUnitPlayer::CurrentPlayer->GetModel();

	if(model)
	{
		model->OnItemAdd.AddUObject(this, &UWD_ItemEventIndicator::AddItem);
		model->OnAddGold.AddUObject(this, &UWD_ItemEventIndicator::AddGold);
		model->OnAddExp.AddUObject(this, &UWD_ItemEventIndicator::AddExp);
	}
}

void UWD_ItemEventIndicator::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}
