#pragma once

#include "CoreMinimal.h"
#include "RPGProject/DataBase/BuffDB.h"
#include "Buff.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_OnEnd, UBuff*);

class IBuffUseCase;

UCLASS()
class RPGPROJECT_API UBuff : public UObject
{
	GENERATED_BODY()

public:
	UBuff();

	FDelegate_OnEnd OnEnd;

	void Initialize(const FBuffData& data);

	void Start();
	void Tick(float deltaTime);
	void End();

	float GetDuration() {return _data.Duration;}

	const FBuffData GetData() {return _data;}

private:
	float _timer = 0;
	FBuffData _data;

	TArray<IBuffUseCase*> _useCases;

};
