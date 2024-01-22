#pragma once

#include <Engine/DataTable.h>

#include "DictionaryDB.generated.h"

USTRUCT(Atomic, BlueprintType)
struct FLevelUpData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int32	NextExp;
};


USTRUCT(Atomic, BlueprintType)
struct FAreaData : public FTableRowBase
{
	GENERATED_BODY()

	int32 ID;

	UPROPERTY(EditAnywhere)
	FText Name;

};