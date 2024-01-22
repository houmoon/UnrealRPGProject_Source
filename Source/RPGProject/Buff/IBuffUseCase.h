#pragma once
#include "RPGProject/Enums/BuffEnums.h"
#include "RPGProject/Global/Defines.h"

class IBuffUseCase
{
	public:
	virtual ~IBuffUseCase() {}
	virtual void OnStart() = 0;
	virtual void OnTick() = 0;
	virtual void OnEnd() = 0;
};

class BuffUseCase_StatFixed : public IBuffUseCase
{
	//버프 유즈케이스는 value와 stat을 기억한다.
	//시작할때, tick할때, end할때의 행동이 각자 다르다.

private:
	EBUFF_STAT _stat;
	float* _statPtr_float;
	int16* _statPtr_int;
	int32 _value;

public:
	BuffUseCase_StatFixed(int32 value,EBUFF_STAT stat);
	virtual void OnStart() override;
	virtual void OnTick() override {}
	virtual void OnEnd() override;
};

class BuffUseCase_StatPercent : public IBuffUseCase
{
	public:
	BuffUseCase_StatPercent(int32 value, EBUFF_STAT stat);
	virtual void OnStart() override;
	virtual void OnTick() override {}
	virtual void OnEnd() override;
};

class BuffUseCase_Invincible : public IBuffUseCase
{
	public:
	BuffUseCase_Invincible(int32 value, EBUFF_STAT stat);
	virtual void OnStart() override;
	virtual void OnTick() override {}
	virtual void OnEnd() override;
};
