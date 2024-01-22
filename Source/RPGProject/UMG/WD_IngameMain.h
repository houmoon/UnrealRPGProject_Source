#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WD_IngameMain.generated.h"

class UBorder;
class UWidgetSwitcher;
class UWD_IngameHUD;
class UWD_DialoguePanel;

UCLASS()
class RPGPROJECT_API UWD_IngameMain : public UUserWidget
{
	GENERATED_BODY()

	public:
	static UWD_IngameMain* CurrentWidget;

	private:
	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget))
	UWidgetSwitcher* _widgetSwitcher;

	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget))
	UWD_IngameHUD* _hud;
	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget))
	UWD_DialoguePanel*	_dialoguePanel;


	public:
	void	SetWidgetIndex(int32 index);
	UWD_IngameHUD*		GetHUD() { return _hud;}
	UWD_DialoguePanel*	GetDialoguePanel() { return _dialoguePanel; }
	
	public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

};
