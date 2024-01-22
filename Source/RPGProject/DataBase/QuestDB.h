#pragma once

#include "Engine/DataTable.h"
#include "RPGProject/Enums/QuestEnums.h"

#include "QuestDB.generated.h"


USTRUCT(Atomic, BlueprintType)
struct FQuestClearData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	EQUEST_CLEAR_TYPE type;

	UPROPERTY(EditAnywhere)
	int32 Value;

	UPROPERTY(EditAnywhere)
	int32 Amount;

	UPROPERTY(EditAnywhere)
	FText CustomDescription = FText::GetEmpty();

	int32 CurrentAmount;

	void OnMsgReceived() { CurrentAmount ++; }

};

USTRUCT(Atomic, BlueprintType)
struct FQuestRewardData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int32 Value;

	UPROPERTY(EditAnywhere)
	int32 Amount;

};


USTRUCT(Atomic, BlueprintType)
struct FQuestData : public FTableRowBase
{
	GENERATED_BODY()
	int32	ID;

	UPROPERTY(EditAnywhere)
	FText Name;

	UPROPERTY(EditAnywhere)
	FText Description;


	//발생 조건 타입과, ID 혹은 수량
	UPROPERTY(EditAnywhere)
	EQUEST_ENABLE_TYPE	EnableType;

	UPROPERTY(EditAnywhere)
	int32 Enable_Value;


	//클리어 조건, 클리어 상태
	UPROPERTY(EditAnywhere)
	EQUEST_STATUS Status = EQUEST_STATUS::DISABLED;

	UPROPERTY(EditAnywhere)
	TArray<FQuestClearData>	ClearConditions;



	UPROPERTY(EditAnywhere)
	int32 RewardExp;

	UPROPERTY(EditAnywhere)
	int32 RewardGold;

	UPROPERTY(EditAnywhere)
	TArray<int32> RewardItem;

};