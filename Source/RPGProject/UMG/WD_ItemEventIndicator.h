#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPGProject/Item/Item.h"
#include "WD_ItemEventIndicator.generated.h"


class UWD_ItemEvent;
class UVerticalBox;

UCLASS()
class RPGPROJECT_API UWD_ItemEventIndicator : public UUserWidget
{
	GENERATED_BODY()

	private:
	static int i;
	static int j;

	UVerticalBox*	_eventView;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	TSubclassOf<UWD_ItemEvent> _itemEventClass;

	public:
	void AddItem(Item* item);
	void AddGold(int32 value);
	void AddExp(int32 value);
	void DropSize();

	public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
