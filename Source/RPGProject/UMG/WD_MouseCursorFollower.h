#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WD_MouseCursorFollower.generated.h"

UCLASS()
class RPGPROJECT_API UWD_MouseCursorFollower : public UUserWidget
{
	GENERATED_BODY()

	public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

};
