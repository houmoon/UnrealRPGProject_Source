#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "RPGProject/Global/Defines.h"
#include "WD_Button.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDelegate_OnClicked);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegate_OnClicked_oneParam, const int32, value);

class UButton;
class UTextBlock;
class UBorder;

UCLASS()
class RPGPROJECT_API UWD_Button : public UUserWidget
{
	GENERATED_BODY()
	
	private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	FText _text;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	UTextBlock* _textArea;

	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = true))
	UButton* _button;

	int32 _value = 0;

	public:
	UPROPERTY(VisibleAnywhere, BlueprintAssignable, Category = "Appearance|Event")
	FDelegate_OnClicked OnClickedButton;

	UPROPERTY(VisibleAnywhere, BlueprintAssignable, Category = "Appearance|Event")
	FDelegate_OnClicked_oneParam OnClickedButton_OneParam;


	public:
	UFUNCTION(BlueprintCallable)
	virtual void BroadCast();

	public:
	void SetValue(int32 value) { _value = value; }
	void SetText(FText text) { _textArea->SetText(text); }

	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;

};
