#include "BTTEnemyMoveTo.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "RPGProject/Enums/UnitEnums.h"
#include "RPGProject/Unit/Enemy/EnemyModelComponent.h"
#include "RPGProject/Unit/Enemy/UnitEnemy.h"

EBTNodeResult::Type UBTTEnemyMoveTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if(m_TargetKey.IsNone())
		return EBTNodeResult::Failed;

	AAIController* controller = OwnerComp.GetAIOwner();

	AUnitEnemy* pEnemy = Cast<AUnitEnemy>(controller->GetPawn());
	if (IsValid(pEnemy))
	{
		pEnemy->StopAnimMontage();
		pEnemy->SetState(EENEMY_STATE::MOVE);
	}

	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
