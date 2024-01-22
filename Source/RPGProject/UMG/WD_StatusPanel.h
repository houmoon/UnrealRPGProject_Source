#pragma once

#include "CoreMinimal.h"
#include "WD_DraggablePanel.h"
#include "RPGProject/DataBase/UnitDB.h"
#include "RPGProject/Enums/ItemEnums.h"

#include "WD_StatusPanel.generated.h"


class UWD_EquipmentSlot;
class UVerticalBox;
class UPlayerModelComponent;
class UTextBlock;

UCLASS()
class RPGPROJECT_API UWD_StatusPanel : public UWD_DraggablePanel
{
	GENERATED_BODY()

	private:
	FMargin margin;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	TSubclassOf<UWD_EquipmentSlot> _equipSlotClass;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UWD_EquipmentSlot* _headSlot;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UWD_EquipmentSlot* _upperSlot;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UWD_EquipmentSlot* _lowerSlot;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UWD_EquipmentSlot* _shoesSlot;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UWD_EquipmentSlot* _weaponSlot;


	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UTextBlock* _nameText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UTextBlock* _levelText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UTextBlock* _HPText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UTextBlock* _MPText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UTextBlock* _EXPText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UTextBlock* _STRText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UTextBlock* _INTText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UTextBlock* _DEXText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UTextBlock* _ATKText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UTextBlock* _DEFText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UTextBlock* _HITText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UTextBlock* _DOGText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UTextBlock* _CRITText;

	public:
	UFUNCTION()
	void RegisterUI(UPlayerModelComponent* model);

	UFUNCTION()
	void UpdateStat(const FPlayerData& data);

private:
	UPlayerModelComponent* _playerModel;
	void initEquipSlot(UWD_EquipmentSlot* slot, EITEM_TYPE type);

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

};
