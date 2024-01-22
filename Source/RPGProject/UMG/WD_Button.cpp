#include "WD_Button.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"


void UWD_Button::BroadCast()
{
	OnClickedButton.Broadcast();
	OnClickedButton_OneParam.Broadcast(_value);
}

void UWD_Button::NativeConstruct()
{
	Super::NativeConstruct();

	_button->OnClicked.Clear();

	_button->OnClicked.AddDynamic(this,&UWD_Button::BroadCast);

}

void UWD_Button::NativePreConstruct()
{
	Super::NativePreConstruct();

	_textArea->SetText(_text);
}
