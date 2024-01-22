#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyMeleeAIController.generated.h"

UCLASS()
class RPGPROJECT_API AEnemyMeleeAIController : public AAIController
{
	GENERATED_BODY()

	private:
	UBehaviorTree*		_behaviorTree;
	UBlackboardData*	_blackboard;

	public:
	//Pawn에 빙의될때 호출하는 함수
	virtual void OnPossess(APawn* _owner) override;
	//Pawn에서 빙의 해제할때 호출하는 함수
	virtual void OnUnPossess() override;
	
};
