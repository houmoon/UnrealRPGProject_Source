

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "../UMG/WD_IngameMain.h"
#include "Gamemode_Ingame.generated.h"


UCLASS()
class RPGPROJECT_API AGamemode_Ingame : public AGameModeBase
{
	GENERATED_BODY()
	
	private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	TSubclassOf<UWD_IngameMain> _mainWidgetClass;
	UWD_IngameMain*				_mainWidget;

	public:
	UFUNCTION(BlueprintCallable)
	UWD_IngameMain*				GetMainWidget();

	UWD_IngameHUD*				GetIngameHUD() {return _mainWidget->GetHUD(); }

	public:
	AGamemode_Ingame();
	~AGamemode_Ingame();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
};
