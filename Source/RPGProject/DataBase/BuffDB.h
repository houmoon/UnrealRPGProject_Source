#pragma once
#include <Engine/DataTable.h>

#include "RPGProject/Enums/BuffEnums.h"
#include "RPGProject/Enums/ItemEnums.h"
#include "BuffDB.generated.h"

USTRUCT(Atomic, BlueprintType)
struct FBuffUseCase : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	EBUFF_TYPE  Type;

	UPROPERTY(EditAnywhere)
	EBUFF_STAT  Stat;

	UPROPERTY(EditAnywhere)
	int32		Value;

};

USTRUCT(Atomic, BlueprintType)
struct FBuffData : public FTableRowBase
{
	GENERATED_BODY()
	int32		ID;

	UPROPERTY(EditAnywhere)
	FText		Name;

	UPROPERTY(EditAnywhere)
	float		Duration;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UTexture2D> IconAsset;

	UPROPERTY(EditAnywhere)
	TArray<FBuffUseCase> UseCases;

};

