#include "Gamemode_Title.h"

#include "Blueprint/UserWidget.h"
#include "RPGProject/Global/Defines.h"
#include "RPGProject/UMG/WD_TitleMain.h"

AGamemode_Title::AGamemode_Title()
{
	_mainWidget = nullptr;
}

AGamemode_Title::~AGamemode_Title()
{
}

void AGamemode_Title::BeginPlay()
{
	Super::BeginPlay();

	if(!_mainWidgetClass)
		return;

	_mainWidget = Cast<UWD_TitleMain>(CreateWidget(GetWorld(), _mainWidgetClass));

	if (IsValid(_mainWidget))
	{
		_mainWidget->AddToViewport();

		// 게임 모드로 전환
		APlayerController* pController = GetWorld()->GetFirstPlayerController();

		FInputModeUIOnly gamemod;
		pController->SetInputMode(gamemod);
		pController->bShowMouseCursor = true;
	}
}

void AGamemode_Title::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
