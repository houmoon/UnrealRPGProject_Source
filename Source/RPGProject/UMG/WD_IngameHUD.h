#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WD_IngameHUD.generated.h"

class UBorder;
class UWD_QuestIndicator;
class UWD_QuestPanel;
class UWD_StatusPanel;
class UWD_Inventory;
class UWD_QuickSlot;
class UWD_ItemToolTip;

UCLASS()
class RPGPROJECT_API UWD_IngameHUD : public UUserWidget
{
	GENERATED_BODY()
	public:
	static UWD_IngameHUD* CurrentWidget;


	private:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UWD_Inventory*		_inventory;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UWD_StatusPanel*	_status;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UWD_QuestPanel* _quest;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UWD_QuickSlot*		_quickslot;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UWD_QuestIndicator* _questIndicator;

	private:
	UFUNCTION(BlueprintCallable)
	void onBorderClicked();

	public:
	UWD_QuickSlot*		GetQuickSlot() {return _quickslot;}
	UWD_Inventory*		GetInventory() {return _inventory;}
	UWD_StatusPanel*	GetStatus() { return _status; }
	UWD_QuestIndicator* GetQuestIndicator() {return _questIndicator; }
	UWD_QuestPanel*		GetQuestPanel() { return _quest; }
	

	void InitializeInventoryUI(int32 size);

	public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
};
