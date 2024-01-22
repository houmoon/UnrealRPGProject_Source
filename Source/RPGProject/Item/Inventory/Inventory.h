#pragma once

#include "CoreMinimal.h"

#include "RPGProject/Enums/ItemEnums.h"
#include "Inventory.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_OnUpdateGold, const int32);
DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_OnAddItem, const int32);

class Item;
class UItemSlot;
class UWD_Inventory;

UCLASS()
class RPGPROJECT_API UInventory : public UObject
{
	GENERATED_BODY()

	public:
	UInventory();
	virtual ~UInventory() override { _world = nullptr; }
	void Initialize(UWorld* world,int32 size);

	private:
	UWorld* _world;
	int32	_size;

	private:
	UPROPERTY()
	TArray<UItemSlot*>	_equipmentItems;
	UPROPERTY()
	TArray<UItemSlot*>	_useItems;
	UPROPERTY()
	TArray<UItemSlot*>	_etcItems;

	UPROPERTY()
	int32				_gold;

	bool					_visibility;

	public:
	UItemSlot* GetItemSlot(int32 index, EITEM_TYPE type);

	FDelegate_OnUpdateGold OnUpdateGold;
	FDelegate_OnAddItem OnAddItem;
	void UpdateGold() { OnUpdateGold.Broadcast(_gold); }
	const int32 GetGold() { return _gold; }

	void SetGold(const int32 gold);

	void AddItem(const int32 id);
	void AddItem(Item* item);
	void DeleteItem(const int32 id);
};
