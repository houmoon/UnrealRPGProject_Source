#pragma once
#include <Engine/DataTable.h>
#include "RPGProject/Enums/ItemEnums.h"
#include "RPGProject/Enums/BuffEnums.h"
#include "ItemDB.generated.h"


USTRUCT(Atomic, BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

	int32		ID;

	UPROPERTY(EditAnywhere)
	FText		Name;

	UPROPERTY(EditAnywhere)
	FText		Description;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UTexture2D> IconAsset;

	UPROPERTY(EditAnywhere)
	EITEM_TYPE Type;
};


USTRUCT(Atomic, BlueprintType)
struct FItemUseCase : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	EITEM_USECASES useCase;
	UPROPERTY(EditAnywhere)
	int32	amount;
};


USTRUCT(Atomic, BlueprintType)
struct FEquipUseCase : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	EBUFF_STAT useCase;
	UPROPERTY(EditAnywhere)
	float	amount;
};


USTRUCT(Atomic, BlueprintType)
struct FEquipItemData : public FItemData
{
	GENERATED_BODY()

	FEquipItemData() { Type = EITEM_TYPE::EQUIPMENT; }

	UPROPERTY(EditAnywhere)
	TArray<FEquipUseCase> UseCases;
};


USTRUCT(Atomic, BlueprintType)
struct FCountItemData : public FItemData
{
	GENERATED_BODY()

	FCountItemData() { Type = EITEM_TYPE::ETC; }

	UPROPERTY(EditAnywhere)
	int16	MaxAmount = 99;
};


USTRUCT(Atomic, BlueprintType)
struct FUseItemData : public FCountItemData
{
	GENERATED_BODY()

	FUseItemData() { Type = EITEM_TYPE::USE; }

	UPROPERTY(EditAnywhere)
	float	CoolTime = 0.f;

	UPROPERTY(EditAnywhere)
	TArray<FItemUseCase> UseCases;

};


USTRUCT(Atomic, BlueprintType)
struct FRewardData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int32 ItemID;

	UPROPERTY(EditAnywhere)
	int16 Amount;
};