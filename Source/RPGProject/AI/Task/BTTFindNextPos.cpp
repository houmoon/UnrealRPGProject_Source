#include "BTTFindNextPos.h"
#include "AIController.h"
#include "behaviortree/blackboardcomponent.h"

#include "NavigationSystem.h"



UBTTFindNextPos::UBTTFindNextPos()
{
	_centerPosKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTFindNextPos, _centerPosKey));
	_nextPosKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTFindNextPos, _nextPosKey));
}

EBTNodeResult::Type UBTTFindNextPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (_centerPosKey.IsNone())
		return EBTNodeResult::Failed;

	FVector vInitPos = OwnerComp.GetBlackboardComponent()->GetValueAsVector(_centerPosKey.SelectedKeyName);

	if (!_rangeKey.IsNone())
		_rangeFromCenter = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(_rangeKey.SelectedKeyName);

	//중심위치에서 반경 범위내의 랜덤한 위치를 가져옴. (네비게이션 시스템이 정해준 영역에 한해)
	FNavLocation location;

	//네비게이션 시스템과 관련된 전역 객체를 가져옴.
	UNavigationSystemV1* pNaviSys = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	pNaviSys->GetRandomPointInNavigableRadius(vInitPos, _rangeFromCenter, location);


	//다음 위치 값 찾기
	FVector vNextPos = location.Location;

	if (_nextPosKey.IsNone())
		return EBTNodeResult::Failed;

	OwnerComp.GetBlackboardComponent()->SetValueAsVector(_nextPosKey.SelectedKeyName, vNextPos);

	return EBTNodeResult::Succeeded;
}


