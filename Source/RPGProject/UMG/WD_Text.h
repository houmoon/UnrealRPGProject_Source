#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WD_Text.generated.h"

class UTextBlock;

UCLASS()
class RPGPROJECT_API UWD_Text : public UUserWidget
{
	GENERATED_BODY()
	
	private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* _text;

	public:
	void SetText(FText text);

	UFUNCTION(BlueprintImplementableEvent)
	void PlayAnim();


	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;

};
