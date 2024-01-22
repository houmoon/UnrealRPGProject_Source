#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "WD_EnemyInfo.generated.h"

class AUnitEnemy;
class UTextBlock;
class UProgressBar;

UCLASS()
class RPGPROJECT_API UWD_EnemyInfo : public UUserWidget
{
	GENERATED_BODY()

	private:
	UTextBlock* _name;
	UProgressBar* _healthbar;

	public:
	void InitializeElements();
	UFUNCTION()
	void SetName(FText name)						{ _name->SetText(name);}
	UFUNCTION()
	void SetHealthBarValue(int32 curHP,int32 HP)	{ _healthbar->SetPercent((float)curHP / (float)HP); }

	public:
	void SetDelegate(AUnitEnemy* enemy);
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

};
