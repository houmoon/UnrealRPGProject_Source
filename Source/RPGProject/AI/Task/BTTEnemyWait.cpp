#include "BTTEnemyWait.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "RPGProject/Enums/UnitEnums.h"
#include "RPGProject/Unit/Enemy/EnemyModelComponent.h"
#include "RPGProject/Unit/Enemy/UnitEnemy.h"
#include "RPGProject/Unit/Player/UnitPlayer.h"


EBTNodeResult::Type UBTTEnemyWait::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AUnitEnemy* pEnemy = Cast<AUnitEnemy>(OwnerComp.GetAIOwner()->GetPawn());

	AAIController* controller = OwnerComp.GetAIOwner();
	AUnitPlayer* pPlayer = Cast<AUnitPlayer>(controller->GetBlackboardComponent()->GetValueAsObject(m_TargetKey.SelectedKeyName));

	if(IsValid(pPlayer))
		return EBTNodeResult::Failed;


	if (IsValid(pEnemy))
	{
		pEnemy->SetState(EENEMY_STATE::IDLE);
	}

	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
