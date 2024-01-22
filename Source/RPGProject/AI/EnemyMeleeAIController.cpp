#include "EnemyMeleeAIController.h"

#include "Behaviortree/blackboarddata.h"
#include "RPGProject/Unit/Enemy/EnemyModelComponent.h"
#include "RPGProject/Unit/Enemy/UnitEnemy.h"


void AEnemyMeleeAIController::OnPossess(APawn* _owner)
{
	Super::OnPossess(_owner);

	AUnitEnemy* enemy = Cast<AUnitEnemy>(_owner);
	if(!IsValid(enemy))
		return;

	_behaviorTree = enemy->GetBehaviourTree();
	_blackboard = enemy->GetBlackBoard();


	if(IsValid(_blackboard))
	{
		UBlackboardComponent* blackboardComp = nullptr;
		UseBlackboard(_blackboard, blackboardComp);

		if(IsValid(_blackboard))
		{
			RunBehaviorTree(_behaviorTree);
		}
	}
}

void AEnemyMeleeAIController::OnUnPossess()
{
	Super::OnUnPossess();
}
