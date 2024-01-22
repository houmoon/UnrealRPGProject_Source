#pragma once

#include "CoreMinimal.h"
#include "RPGProject/Buff/Buff.h"
#include "BuffManager.generated.h"

class UDataTable;

UCLASS()
class UBuffManager : public UObject
{
	GENERATED_BODY()

	public: static UBuffManager* GetInstance();
	private: static UBuffManager* _instance;

	public:

	private:
	UPROPERTY()
	TMap<int32, UBuff*> _buffs;

	public:
	UBuff* GetBuff(int32 id);
	void Initialize(UDataTable* database);

};
