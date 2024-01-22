#include "BTDWithinRange.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"
#include "GameFramework/Character.h"


UBTDWithinRange::UBTDWithinRange()
{

	//블랙보드 컴포넌트로서 키를 넣어줄때, 키를 정해줄 수 있는 종류를 제한할 수 있다.
	_targetKey.AddObjectFilter(this,GET_MEMBER_NAME_CHECKED(UBTDWithinRange, _targetKey),AActor::StaticClass());
	_rangeKey.AddFloatFilter(this, GET_MEMBER_NAME_CHECKED(UBTDWithinRange, _rangeKey));

}

bool UBTDWithinRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	//범위를 체크할 타겟을 가져온다.
	if (_targetKey.IsNone()) //BT가 블랙보드에 연동되지 않을 때
		return false;
	
	ACharacter* pTarget = Cast<ACharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(_targetKey.SelectedKeyName));
	if (!IsValid(pTarget))
		return false;

	float frange = _range;
	if (!_rangeKey.IsNone()) //BT가 블랙보드와 연동되었을 때
	{
		frange = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(_rangeKey.SelectedKeyName); //블랙보드에서 키를 통해 값을 가져온다.
	}


	//타겟이 범위안에 있는지 체크한다.
	AAIController* pController = OwnerComp.GetAIOwner();
	APawn* pPawn = pController->GetPawn();


	if (IsValid(pPawn))
	{
		float distance = FVector::Distance(pTarget->GetActorLocation(), pPawn->GetActorLocation());

		if (distance < frange)
			return true;
	}

	return false;
}
