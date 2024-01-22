

#pragma once

#include "CoreMinimal.h"
#include "WD_InventorySlot.h"

#include "WD_EquipmentSlot.generated.h"


UCLASS()
class RPGPROJECT_API UWD_EquipmentSlot : public UWD_InventorySlot
{
	GENERATED_BODY()

	public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& geometry, float deltaTime) override;

	virtual FReply NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	//Drag And Drop
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
};
