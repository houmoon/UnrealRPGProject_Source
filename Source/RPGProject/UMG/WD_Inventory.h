#pragma once

#include "CoreMinimal.h"
#include "WD_DraggablePanel.h"
#include "WD_ItemToolTip.h"
#include "Blueprint/UserWidget.h"
#include "WD_Inventory.generated.h"


class Item;
class UWD_InventoryBackpack;

UCLASS()
class RPGPROJECT_API UWD_Inventory : public UWD_DraggablePanel
{
	GENERATED_BODY()

	private:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UTextBlock*				_goldText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UWD_InventoryBackpack* _equipItemView;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UWD_InventoryBackpack* _useItemView;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UWD_InventoryBackpack* _etcItemView;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UWD_ItemToolTip* _itemTooltip;

	void onHovered(UObject* _data, bool isHovered);
	void UpdateGold(const int32 gold);

	public:
	void InitSlots(int32 size);

	public:
	virtual void NativeConstruct() override;
};
