

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPGProject/Global/Defines.h"
#include "RPGProject/Item/ItemSlot.h"
#include "WD_InventorySlot.generated.h"

class UCanvasPanelSlot;
class UWD_ItemToolTip;
class UItemSlot;
class UImage;
class UTextBlock;
class Item;


UCLASS()
class RPGPROJECT_API UWD_InventorySlot : public UUserWidget
{
	GENERATED_BODY()

	protected:
	EITEM_TYPE			_type;

	private:
	UCanvasPanelSlot*	_canvasSlot;
	static UWD_ItemToolTip*	_tooltip;
	UItemSlot*	_item = nullptr;
	UTextBlock*	_itemAmount = nullptr;
	UImage*		_itemImg = nullptr;
	UImage*		_cooltime = nullptr;

	UPROPERTY(EditAnywhere)
	UMaterialInterface*		_cooltimeMT = nullptr;

	UMaterialInstanceDynamic* _cooltimeMTInstance = nullptr ;

	FReply DetectDrag(const FPointerEvent& inMouseEvent, UWidget* widgetDetectingDrag, FKey dragKey);

	public:
	// InventoryItemData 를 입력받아서 초기화하는 함수
	UFUNCTION()
	void UpdateSlot(UTexture2D* iconImg, uint8 amount);
	void SetType(EITEM_TYPE type) {_type = type;}
	void SetTooltip(UWD_ItemToolTip* tooltip) {_tooltip = tooltip;}

	EITEM_TYPE GetType(EITEM_TYPE type) { return _type; }

	void SetItemSlot(UItemSlot* item) {_item = item; if(_item) _item->OnUpdateSlot.BindUObject(this,&UWD_InventorySlot::UpdateSlot);}

	public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& geometry, float deltaTime) override;

	virtual FReply NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	//Drag And Drop
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	//Tooltip
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
};
