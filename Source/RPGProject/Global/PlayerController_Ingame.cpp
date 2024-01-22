#include "PlayerController_Ingame.h"

APlayerController_Ingame::APlayerController_Ingame()
{
}

void APlayerController_Ingame::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	/*
	FHitResult result = {};
	//두번째 패러미터는 성능을 많이 잡아먹으므로 false를 두는게 좋음
	bool bHit = GetHitResultUnderCursor(ECC_EngineTraceChannel5,false,result);

	if (bHit)
	{
		if (Cast<AUnitPlayer>(result.GetActor()))
			CurrentMouseCursor = EMouseCursor::GrabHand;
		else
			CurrentMouseCursor = EMouseCursor::Default;	
	}
	*/
}
