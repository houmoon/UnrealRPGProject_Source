#include "Buff.h"

#include "IBuffUseCase.h"
#include "RPGProject/UMG/WD_IngameHUD.h"

UBuff::UBuff()
{
	
}

void UBuff::Initialize(const FBuffData& data)
{
	_data = data;

	if (_data.IconAsset.IsPending())
		_data.IconAsset.LoadSynchronous();


	for(int i=0; i<data.UseCases.Num(); i++)
	{
		//버프 유즈케이스 별로 객체를 정의해서 포인터와 연결
		switch(data.UseCases[i].Type)
		{
		case EBUFF_TYPE::STAT_FIXED:
		{
			BuffUseCase_StatFixed* newUseCase = new BuffUseCase_StatFixed(data.UseCases[i].Value,data.UseCases[i].Stat);
			_useCases.Add(newUseCase);
			break;
		}
		case EBUFF_TYPE::STAT_PERCENT:
		{
			BuffUseCase_StatPercent* newUseCase = new BuffUseCase_StatPercent(data.UseCases[i].Value, data.UseCases[i].Stat);
			_useCases.Add(newUseCase);
			break;
		}
		case EBUFF_TYPE::INVINCIBLE:
		{
			BuffUseCase_Invincible* newUseCase = new BuffUseCase_Invincible(data.UseCases[i].Value, data.UseCases[i].Stat);
			_useCases.Add(newUseCase);
			break;
		}
		default: ;
		}
	}

}

void UBuff::Start()
{
	_timer = 0;

	for(int32 i =0; i<_useCases.Num(); i++)
	{
		if(_useCases[i])
			_useCases[i]->OnStart();
		else
		{
			UE_LOG(LogTemp,Error,TEXT("Cant Find useCase."));
		}
			
	}
}

void UBuff::Tick(float deltaTime)
{
	_timer += deltaTime;

	if(_timer >= _data.Duration)
	{
		End();
		return;
	}
		

	for (auto useCase : _useCases)
	{
		useCase->OnTick();
	}
}

void UBuff::End()
{
	_timer = 0;

	for (auto useCase : _useCases)
	{
		useCase->OnEnd();
	}

	OnEnd.Broadcast(this);
}
