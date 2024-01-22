#pragma once

#include "CoreMinimal.h"


class UDataTable;

//아이템 DB 데이터를 저장하고, ID를 통해 아이템 정보를 불러오는 매니저
class CooltimeManager
{
	public: static CooltimeManager* GetInstance();
	private: static CooltimeManager* _instance;

	public:
	CooltimeManager();


	private:
	TMap<int32, float> _cooltimes;
	TArray<float*> _cooltimeQueue;

	public:
	float GetCurrentCooltime(const int32 ID);
	void RegisterCooltime(const int32 ID, float originalCooltime);
	void Initialize(UDataTable* database);
	void Initialize_Buff(UDataTable* database);
	void OnTick(float deltaTime);

};
