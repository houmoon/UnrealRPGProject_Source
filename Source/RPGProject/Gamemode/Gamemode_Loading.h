#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Gamemode_Loading.generated.h"

class UWD_TitleMain;

UCLASS()
class RPGPROJECT_API AGamemode_Loading : public AGameModeBase
{
	GENERATED_BODY()

	public:
	AGamemode_Loading();
	~AGamemode_Loading();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
};
