

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Gamemode_Title.generated.h"

class UWD_TitleMain;

UCLASS()
class RPGPROJECT_API AGamemode_Title : public AGameModeBase
{
	GENERATED_BODY()

	private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	TSubclassOf<UWD_TitleMain> _mainWidgetClass;
	UWD_TitleMain* _mainWidget;

	public:
	UWD_TitleMain* GetMainWidget() { return _mainWidget; }
	public:
	AGamemode_Title();
	~AGamemode_Title();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
};
