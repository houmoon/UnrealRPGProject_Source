#include "WD_DraggablePanel.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/CanvasPanelSlot.h"
#include "RPGProject/Global/Defines.h"
#include "RPGProject/Unit/Player/UnitPlayer.h"

int32 UWD_DraggablePanel::OpenedPanelAmount = 0;

FEventReply UWD_DraggablePanel::OnTitleBarMouseButtonDown(FGeometry geometry, const FPointerEvent& inputEvent)
{
	FVector2D MousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(this);

	UCanvasPanelSlot* slot = Cast<UCanvasPanelSlot>(Slot);

	if (slot)
	{
		_mousePos = UWidgetLayoutLibrary::GetMousePositionOnViewport(this) - slot->GetPosition();
	}
		

	updatePosition();
	_isDragging = true;

	return	FEventReply(true);
}

void UWD_DraggablePanel::NativeOnAddedToFocusPath(const FFocusEvent& InFocusEvent)
{
	Super::NativeOnAddedToFocusPath(InFocusEvent);

	UCanvasPanelSlot* slot = Cast<UCanvasPanelSlot>(Slot);

	if (slot)
	{
		slot->SetZOrder(GetParent()->GetChildrenCount() - 1);
	}

}

void UWD_DraggablePanel::NativeOnFocusLost(const FFocusEvent& InFocusEvent)
{
	Super::NativeOnFocusLost(InFocusEvent);

	UCanvasPanelSlot* slot = Cast<UCanvasPanelSlot>(Slot);

	if (slot)
	{
		slot->SetZOrder(GetParent()->GetChildrenCount() - 2);
	}
}


void UWD_DraggablePanel::updatePosition()
{
	FVector2D pos = UWidgetLayoutLibrary::GetMousePositionOnViewport(this) - _mousePos;

	UCanvasPanelSlot* slot = Cast<UCanvasPanelSlot>(Slot);

	if (slot)
		slot->SetPosition(pos);
}

void UWD_DraggablePanel::OpenPanel()
{
	AUnitPlayer* player = AUnitPlayer::CurrentPlayer;
	if(player)
		player->SetInputMode(false);

	
	OpenedPanelAmount++;
	SetVisibility(ESlateVisibility::Visible);
}

void UWD_DraggablePanel::ExitPanel()
{
	OpenedPanelAmount--;

	if(OpenedPanelAmount <= 0)
	{
		AUnitPlayer* player = AUnitPlayer::CurrentPlayer;
		if (player)
			player->SetInputMode(true);
	}

	SetVisibility(ESlateVisibility::Hidden);
}

void UWD_DraggablePanel::TogglePanel()
{
	if(GetVisibility() == ESlateVisibility::Hidden)
		OpenPanel();
	else
		ExitPanel();
}

FReply UWD_DraggablePanel::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);

	_isDragging = false;

	return FReply::Handled();
}

void UWD_DraggablePanel::NativeConstruct()
{
	Super::NativeConstruct();
	if(_titleBox)
		_titleBox->OnMouseButtonDownEvent.BindDynamic(this,&UWD_DraggablePanel::OnTitleBarMouseButtonDown);

	if(_exitButton)
		_exitButton->OnClicked.AddDynamic(this,&UWD_DraggablePanel::ExitPanel);
}

void UWD_DraggablePanel::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry,InDeltaTime);

	if(_isDragging)
		updatePosition();

}
