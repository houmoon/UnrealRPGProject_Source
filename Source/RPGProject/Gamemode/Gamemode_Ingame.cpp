#include "Gamemode_Ingame.h"

#include "RPGProject/Global/CooltimeManager.h"
#include "RPGProject/Global/Defines.h"
#include "RPGProject/Unit/Player/UnitPlayer.h"


UWD_IngameMain* AGamemode_Ingame::GetMainWidget()
{
	return _mainWidget;
}

AGamemode_Ingame::AGamemode_Ingame()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;

	_mainWidget = nullptr;
}

AGamemode_Ingame::~AGamemode_Ingame()
{
}

void AGamemode_Ingame::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* playerController = GetWorld()->GetFirstPlayerController();
	playerController->PlayerCameraManager->StartCameraFade(1.0f, 0.0f, 0.5f, FLinearColor::Black, false, true);


	if(!_mainWidgetClass)
		return;

	_mainWidget = Cast<UWD_IngameMain>(CreateWidget(GetWorld(), _mainWidgetClass));

	if (IsValid(_mainWidget))
	{
		_mainWidget->AddToViewport();

		// 게임 모드로 전환
		APlayerController* pController = GetWorld()->GetFirstPlayerController();

		FInputModeGameOnly gamemod;
		pController->SetInputMode(gamemod);
		pController->bShowMouseCursor = false;
	}
}

void AGamemode_Ingame::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CooltimeManager::GetInstance()->OnTick(DeltaSeconds);
}
