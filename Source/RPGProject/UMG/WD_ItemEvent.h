

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WD_ItemEvent.generated.h"

class UTextBlock;
class UWD_ItemEventIndicator;
class Item;

UCLASS()
class RPGPROJECT_API UWD_ItemEvent : public UUserWidget
{
	GENERATED_BODY()

	private:
	UPROPERTY(meta = (AllowPrivateAccess = true,BindWidget))
	UTextBlock* _eventText;

	FWidgetAnimationDynamicEvent _fadeOutEndDelegate;

	UFUNCTION()
	void onFadeOutFinished();

	private:
	UWD_ItemEventIndicator* _parent;

	UPROPERTY(Meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* _fadeOutAnim;

	public:
	void SetParent(UWD_ItemEventIndicator* parent) { _parent = parent;}
	// InventoryItemData 를 입력받아서 초기화하는 함수
	void InitFromData(Item* _Data);
	void InitFromGoldData(int32 gold);
	void InitFromExpData(int32 exp);

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& geometry, float deltaTime) override;
	
};
