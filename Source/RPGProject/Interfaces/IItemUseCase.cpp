#pragma once

#include "IItemUseCase.h"

#include "Kismet/GameplayStatics.h"
#include "RPGProject/Global/CooltimeManager.h"
#include "RPGProject/Global/Defines.h"
#include "RPGProject/Unit/Player/PlayerModelComponent.h"
#include "RPGProject/Unit/Player/UnitPlayer.h"


IItemUseCase::IItemUseCase(int32 amount)
{
	_amount = amount;
}

bool IItemUseCase::Use()
{
	return true;
}

bool UseCase_HPIncrease::Use()
{
	AUnitPlayer* player = AUnitPlayer::CurrentPlayer;

	
	if(player)
	{
		if(player->GetModel()->GetData()->CurHP >= player->GetModel()->GetData()->HP)
			return false;

		player->GetModel()->RecoverHP(_amount);
		return true;
	}
	else
	{
		return false;
	}
		
}

bool UseCase_MPIncrease::Use()
{
	AUnitPlayer* player = AUnitPlayer::CurrentPlayer;

	if (player)
	{
		if (player->GetModel()->GetData()->CurMP >= player->GetModel()->GetData()->MP)
			return false;

		player->GetModel()->RecoverMP(_amount);
		return true;
	}

	return false;
}

bool UseCase_Buff::Use()
{
	AUnitPlayer* player = AUnitPlayer::CurrentPlayer;

	if (player)
	{
		//이미 버프가 발동중이라면 false 반환.
		if(CooltimeManager::GetInstance()->GetCurrentCooltime(_amount) > 0.f)
			return false;

		//버프 id를 호출.
		player->GetModel()->RegisterBuff(_amount);

		return true;
	}

	return false;
}
