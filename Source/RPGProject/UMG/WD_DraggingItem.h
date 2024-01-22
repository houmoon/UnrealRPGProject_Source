#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "WD_DraggingItem.generated.h"

class UItemSlot;
enum class EITEM_TYPE : uint32;

UCLASS()
class RPGPROJECT_API UWD_DraggingItem : public UDragDropOperation
{
	GENERATED_BODY()
	
	private:
	UItemSlot* _item;

	public:
	void SetItemSlot(UItemSlot* item) { _item = item; }
	UItemSlot* GetItemSlot() {return _item;}
};
