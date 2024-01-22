

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerController_Ingame.generated.h"

/**
 * 
 */
UCLASS()
class RPGPROJECT_API APlayerController_Ingame : public APlayerController
{
	GENERATED_BODY()
	
	public:
	APlayerController_Ingame();
	virtual void Tick(float deltaTime) override;
};
