#pragma once

#include "CoreMinimal.h"

#include "GlobalGameInstance.generated.h"


class UDataTable;

UCLASS()
class RPGPROJECT_API UGlobalGameInstance : public UGameInstance
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FColor EnemyDamage_Color;

	UPROPERTY(EditAnywhere)
	FColor PlayerDamage_Color;

	UPROPERTY(EditAnywhere)
	FColor PlayerRecovery_Color;

	UPROPERTY(EditAnywhere)
	UDataTable* DT_Effect;

	UPROPERTY(EditAnywhere)
	UDataTable* DT_Enemy;

	UPROPERTY(EditAnywhere)
	UDataTable* DT_EquipItem;

	UPROPERTY(EditAnywhere)
	UDataTable* DT_UseItem;

	UPROPERTY(EditAnywhere)
	UDataTable* DT_EtcItem;

	UPROPERTY(EditAnywhere)
	UDataTable* DT_LevelUp;

	UPROPERTY(EditAnywhere)
	UDataTable* DT_Quest;

	UPROPERTY(EditAnywhere)
	UDataTable* DT_Area;

	UPROPERTY(EditAnywhere)
	UDataTable* DT_Dialogue;

	UPROPERTY(EditAnywhere)
	UDataTable* DT_Selection;

	UPROPERTY(EditAnywhere)
	UDataTable* DT_Buff;

	public:
	UGlobalGameInstance();
	~UGlobalGameInstance();


	public:
	virtual void Init() override;

};