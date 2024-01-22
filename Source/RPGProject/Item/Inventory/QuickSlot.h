#pragma once

#include "CoreMinimal.h"

#include "QuickSlot.generated.h"

class UWD_QuickSlot;
class UItemSlot;

UCLASS()
class RPGPROJECT_API UQuickSlot : public UObject
{
	GENERATED_BODY()

	public:
	UQuickSlot();
	virtual ~UQuickSlot() override { _world = nullptr; }
	void Initialize(UWorld* world,int32 size);

	private:
	UWorld* _world;
	int32	_size;
	UWD_QuickSlot* _quickSlotUI;

	private:
	UPROPERTY()
	TArray<UItemSlot*>	_itemSlots;

	bool				_visibility;

	public:
	UItemSlot* GetItemSlot(int32 index);
	void Use(int32 index);

};
