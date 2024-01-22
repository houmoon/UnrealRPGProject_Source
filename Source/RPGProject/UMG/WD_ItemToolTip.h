#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPGProject/Enums/ItemEnums.h"
#include "WD_ItemToolTip.generated.h"

class Item;
class UTextBlock;
class UImage;

UCLASS()
class RPGPROJECT_API UWD_ItemToolTip : public UUserWidget
{
	GENERATED_BODY()
	
	private:
	UTextBlock* _name;
	UTextBlock* _description;
	UTextBlock* _typedesc;

	UImage*	_image;

	public:
	void SetData(Item* item);
	void SetName(FText name);
	void SetDescription(FText description);
	void SetTypeDescription(EITEM_TYPE type);
	void SetImage(UTexture2D* img);

	public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& geometry, float deltaTime) override;
	void SetToMousePosition();
	void SetToWidgetPosition(UWidget* widget);
};
