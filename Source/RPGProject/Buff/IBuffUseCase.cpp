#include "IBuffUseCase.h"

#include "RPGProject/Global/Defines.h"
#include "RPGProject/Unit/Player/PlayerModelComponent.h"
#include "RPGProject/Unit/Player/UnitPlayer.h"

BuffUseCase_StatFixed::BuffUseCase_StatFixed(int32 value, EBUFF_STAT stat)
{
	_stat = stat;
	_value = value;
}

void BuffUseCase_StatFixed::OnStart()
{
	AUnitPlayer* player = AUnitPlayer::CurrentPlayer;
	if(!player)
		return;

	player->GetModel()->AddStat(_stat,_value);
}

void BuffUseCase_StatFixed::OnEnd()
{
	AUnitPlayer* player = AUnitPlayer::CurrentPlayer;
	if (!player)
		return;

	player->GetModel()->AddStat(_stat, -_value);
}

BuffUseCase_StatPercent::BuffUseCase_StatPercent(int32 value, EBUFF_STAT stat)
{
}

void BuffUseCase_StatPercent::OnStart()
{

}

void BuffUseCase_StatPercent::OnEnd()
{

}

BuffUseCase_Invincible::BuffUseCase_Invincible(int32 value, EBUFF_STAT stat)
{
}

void BuffUseCase_Invincible::OnStart()
{

}

void BuffUseCase_Invincible::OnEnd()
{

}
