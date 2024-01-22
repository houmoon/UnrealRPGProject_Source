#include "WD_Text.h"
#include "Components/TextBlock.h"

void UWD_Text::SetText(FText text)
{
	_text->SetText(text);
}

void UWD_Text::NativeConstruct()
{
	Super::NativeConstruct();
}

void UWD_Text::NativePreConstruct()
{
	Super::NativePreConstruct();
}
