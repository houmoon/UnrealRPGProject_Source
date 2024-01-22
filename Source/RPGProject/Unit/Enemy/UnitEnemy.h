#pragma once

#include "CoreMinimal.h"
#include "RPGProject/Enums/UnitEnums.h"

#include "RPGProject/Unit/Unit.h"
#include "UnitEnemy.generated.h"


class UBehaviorTree;
class UBlackboardData;
struct FEnemyData;
class UWidgetComponent;
class UEnemyModelComponent;

UCLASS()
class RPGPROJECT_API AUnitEnemy : public AUnit
{
	GENERATED_BODY()

	//Getter
	public:
	virtual FVector GetLocalMoveDir() override;
	const EENEMY_STATE& GetState();
	const FEnemyData* const GetData();
	UEnemyModelComponent* const GetModel() { return _enemyModel; }
	UBehaviorTree* const GetBehaviourTree();
	UBlackboardData* const GetBlackBoard();
	

	//Messages
	virtual void Attack() override;
	virtual void Damage(int32 damage) override;
	virtual void Death(const int32 ID) override;
	void SetAttackTarget(AUnit* target) { _attackTarget = target; }
	void DamageToTarget();
	void Burn();
	void GiveItemsToPlayer();
	void SetState(EENEMY_STATE state);

	//Private Attributes
	private:
	//모델 데이터
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Enemy", meta = (AllowPrivateAccess = "true"))
	UEnemyModelComponent* _enemyModel;

	//위젯컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Enemy", meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* _widgetComponent;

	//공격 대상
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Enemy", meta = (AllowPrivateAccess = "true"))
	AUnit*		_attackTarget;

	UPROPERTY(EditAnywhere, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* _deathMontage;

	UPROPERTY(EditAnywhere, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* _attackMeleeMontage;

	UPROPERTY(EditAnywhere, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* _hitReactionMontage;

	bool _isBurning;
	float _burnIntense;


	//Initializer & Cycle Callbacks
	public:
	AUnitEnemy();
	virtual void Tick(float DeltaSeconds) override;

	protected:
	virtual void BeginPlay() override;
	

};
