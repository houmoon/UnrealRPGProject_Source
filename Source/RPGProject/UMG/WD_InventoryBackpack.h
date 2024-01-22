#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPGProject/Enums/ItemEnums.h"
#include "WD_InventoryBackpack.generated.h"


class UWD_ItemToolTip;
class UWD_InventorySlot;
class UUniformGridPanel;

UCLASS()
class RPGPROJECT_API UWD_InventoryBackpack : public UUserWidget
{
	GENERATED_BODY()
	
	private:
	UUniformGridPanel* _slotView = nullptr;
	TArray<UWD_InventorySlot*> _slots;
	int32 _size;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	TSubclassOf<UWD_InventorySlot> _slotClass;

	public:
	void InitSlots(int32 amount, EITEM_TYPE type, UWD_ItemToolTip* tooltip);

	public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
};
