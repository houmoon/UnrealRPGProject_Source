#pragma once

#include "CoreMinimal.h"
#include "RPGProject/DataBase/UnitDB.h"
#include "RPGProject/Enums/UnitEnums.h"
#include "RPGProject/Unit/UnitModelComponent.h"

#include "EnemyModelComponent.generated.h"

class UBlackboardData;
class UBehaviorTree;

UCLASS()
class RPGPROJECT_API UEnemyModelComponent : public UUnitModelComponent
{
	GENERATED_BODY()

	friend class AUnitEnemy;

	//Getter
	public:
	static FColor			damageColor;
	virtual int32			GetDamage() override;

	//Messages & Delegates
	protected:
	virtual void Init(UWorld* world) override;
	virtual void Damage(int32 damage) override;
	virtual void Death() override;
	private:
	void SetState(EENEMY_STATE state) { if (EENEMY_STATE::DEATH != _state) _state = state; }

	public:
	void UpdateHP()						{ OnUpdateHP.Broadcast(_enemyData.CurHP, _enemyData.HP); }
	void UpdateName()					{ OnUpdateName.Broadcast(_enemyData.Name); }
	

	//Private Attributes
	private:
	UPROPERTY(EditAnywhere, category = "Enemy Data", meta = (AllowPrivateAccess = "true"))
	FEnemyData _enemyData;

	UPROPERTY(EditAnywhere, category = "Enemy Data", meta = (AllowPrivateAccess = "true"))
	EENEMY_STATE _state;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Data", meta = (RowType = "EnemyData", AllowPrivateAccess = "true"))
	FDataTableRowHandle _dataBase;

	//행동트리
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* _behaviorTree;

	//블랙보드
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UBlackboardData* _blackBoardData;
	

public:	
	UEnemyModelComponent();
protected:
	virtual void BeginPlay() override;
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void InitializeComponent() override;

		
};
