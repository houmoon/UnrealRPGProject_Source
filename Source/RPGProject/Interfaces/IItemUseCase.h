#pragma once

#include "CoreMinimal.h"

class AUnitPlayer;

class IItemUseCase
{
	protected:
	int32			_amount = 0;

	public:
	IItemUseCase(int32 amount);
	virtual ~IItemUseCase() {}
	virtual bool Use();
};

class UseCase_HPIncrease : public IItemUseCase
{
	public:
	UseCase_HPIncrease(int32 amount) : IItemUseCase(amount) {}
	bool Use() override;
};

class UseCase_MPIncrease : public IItemUseCase
{
	public:
	UseCase_MPIncrease(int32 amount) : IItemUseCase(amount) {}
	bool Use() override;
};

class UseCase_Buff : public IItemUseCase
{
	public:
	UseCase_Buff(int32 id) : IItemUseCase(id) {}
	bool Use() override;
};