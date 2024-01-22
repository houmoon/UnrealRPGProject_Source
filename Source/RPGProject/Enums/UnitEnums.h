#pragma once

UENUM()
enum class EENEMY_TYPE : uint8
{
	MELEE,
	RANGE,
	BOSS
};

UENUM(BlueprintType)
enum class EENEMY_STATE : uint8
{
	IDLE			= 0,
	MOVE			= 1,
	MELEE_ATTACK	= 2,
	RANGE_ATTACK	= 3,
	HIT				= 4,
	DEATH			= 5
};