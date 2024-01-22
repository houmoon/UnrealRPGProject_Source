#pragma once

#include "CoreMinimal.h"
#include "RPGProject/DataBase/UnitDB.h"


//적 DB를 저장하고, ID를 통해 적 정보를 불러오는 매니저
class EnemyDataManager
{
	public: static EnemyDataManager* GetInstance();
	private: static EnemyDataManager* _instance;

	public:
	//적 DB 초기화
	void SetDataTable(class UDataTable* dataTable);
	const FEnemyData* const GetEnemyData(const int32 ID);

	private:
	//적 데이터 테이블
	class UDataTable* _dataTable;

	//적 데이터 집합
	TMap<int32, const FEnemyData>		_enemyDatas;


};
