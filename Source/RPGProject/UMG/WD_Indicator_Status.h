#pragma once

#include "CoreMinimal.h"
#include "WD_Buff.h"
#include "Blueprint/UserWidget.h"
#include "WD_Indicator_Status.generated.h"

class UBuff;
class UHorizontalBox;
class UPlayerModelComponent;
class UProgressBar;
class UTextBlock;

UCLASS()
class RPGPROJECT_API UWD_Indicator_Status : public UUserWidget
{
	GENERATED_BODY()

	private:
	static int buffCount;

	UProgressBar* _HPBar;
	UTextBlock* _HPText;

	UProgressBar* _MPBar;
	UTextBlock* _MPText;

	UProgressBar* _EXPBar;
	UTextBlock* _EXPText;

	UTextBlock* _NameText;
	UTextBlock* _LevelText;

	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget))
	UHorizontalBox* _buffs;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	TSubclassOf<UWD_Buff> _buffClass;

public:

	private:
	UFUNCTION()
	void RegisterUI(UPlayerModelComponent* model);
	UFUNCTION()
	void UpdateHPBar(int32 CurrentHP, int32 MaxHP);

	UFUNCTION()
	void UpdateMPBar(int32 currentMP, int32 maxMP);
	UFUNCTION()
	void UpdateEXPBar(int32 currentEXP, int32 maxEXP);
	UFUNCTION()
	void UpdateLevel(int32 currentLevel);
	UFUNCTION()
	void UpdateName(FText name);
	UFUNCTION()
	void RegisterBuff(UBuff* buff);

	public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

};
