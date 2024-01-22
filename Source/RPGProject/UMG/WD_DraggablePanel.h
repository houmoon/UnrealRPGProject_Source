#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WD_DraggablePanel.generated.h"


class UButton;
class UBorder;

UCLASS()
class RPGPROJECT_API UWD_DraggablePanel : public UUserWidget
{
	GENERATED_BODY()

public:
	static int32 OpenedPanelAmount;

private:
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = true))
	UBorder* _titleBox;
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = true))
	UButton* _exitButton;

public:
	UFUNCTION()
	FEventReply OnTitleBarMouseButtonDown(FGeometry geometry, const FPointerEvent& inputEvent);

	virtual void NativeOnAddedToFocusPath(const FFocusEvent& InFocusEvent) override;
	virtual void NativeOnFocusLost(const FFocusEvent& InFocusEvent) override;

private:

	void updatePosition();

	FVector2D _mousePos;
	bool	_isDragging = false;

	public:
	void OpenPanel();
	UFUNCTION()
	void ExitPanel();
	void TogglePanel();

	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

};
