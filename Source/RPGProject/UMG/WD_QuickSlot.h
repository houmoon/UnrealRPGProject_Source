#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WD_QuickSlot.generated.h"


class UQuickSlot;
class UItemSlot;
class UHorizontalBox;
class UWD_ItemToolTip;
class UWD_InventorySlot;

UCLASS()
class RPGPROJECT_API UWD_QuickSlot : public UUserWidget
{
	GENERATED_BODY()
	
	private:
	UHorizontalBox* _slotView = nullptr;
	TArray<UWD_InventorySlot*> _slots;
	int32 _size;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	TSubclassOf<UWD_InventorySlot> _slotClass;

	public:
	void InitSlots(UQuickSlot* quickSlot, int32 amount);

	public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
};
