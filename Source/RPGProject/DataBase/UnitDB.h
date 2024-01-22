#pragma once

#include <Engine/DataTable.h>


#include "UnitDB.generated.h"

USTRUCT(Atomic, BlueprintType)
struct FUnitData : public FTableRowBase
{
	GENERATED_BODY()

	int32	ID;

	UPROPERTY(EditAnywhere)
	FText	Name;

	UPROPERTY(EditAnywhere)
	float	MoveSpeed;
};

USTRUCT(Atomic, BlueprintType)
struct FNpcData : public FUnitData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int32 StartDialogueID;
};

USTRUCT(Atomic, BlueprintType)
struct FCombatUnitData : public FUnitData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int32	HP;
	int32	CurHP;

	UPROPERTY(EditAnywhere)
	int16	Level;


	//1st Stat
	UPROPERTY(EditAnywhere)
	float	ATK;
	UPROPERTY(EditAnywhere)
	float	DEF;
	UPROPERTY(EditAnywhere)
	float	HIT;
	UPROPERTY(EditAnywhere)
	float	DOG;
	UPROPERTY(EditAnywhere)
	float	CRIT;
	UPROPERTY(EditAnywhere)
	float	AtkSpeed;
};

USTRUCT(Atomic, BlueprintType)
struct FPlayerData : public FCombatUnitData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int32	MP;
	int32	CurMP;

	int32	CurExp;

	UPROPERTY(EditAnywhere)
	float	SprintSpeed;

	//2nd Stat (For Player)
	UPROPERTY(EditAnywhere)
	int16	STR;
	UPROPERTY(EditAnywhere)
	int16	INT;
	UPROPERTY(EditAnywhere)
	int16	DEX;

};


USTRUCT(Atomic, BlueprintType)
struct FEnemyData : public FCombatUnitData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float DetectRange;

	UPROPERTY(EditAnywhere)
	float AttackRange;

	UPROPERTY(EditAnywhere)
	TArray<int32> RewardIDs;

	UPROPERTY(EditAnywhere)
	int32 RewardGold;

	UPROPERTY(EditAnywhere)
	int32 RewardEXP;
};
