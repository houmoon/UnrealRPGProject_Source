#include "BTSDetectPlayer.h"

#include "AIController.h"
#include "behaviortree/blackboardcomponent.h"
#include "Kismet/GameplayStatics.h"
#include "RPGProject/DataBase/UnitDB.h"

#include "RPGProject/Unit/Enemy/EnemyModelComponent.h"
#include "RPGProject/Unit/Enemy/UnitEnemy.h"
#include "RPGProject/Unit/Player/UnitPlayer.h"

UBTSDetectPlayer::UBTSDetectPlayer()
{
	//서비스 설명
	NodeName = TEXT("일정 시간마다 탐지 범위 내 플레이어를 탐색.");

	//서비스 호출 간격 (초 단위)
	Interval = 0.5f;
}

UBTSDetectPlayer::~UBTSDetectPlayer()
{
}

void UBTSDetectPlayer::TickNode(UBehaviorTreeComponent& _ownCom, uint8* _nodeMemory, float _DT)
{
	Super::TickNode(_ownCom, _nodeMemory, _DT);

	// 빙의한 몬스터에 대한 참조를 얻는다.
	AAIController* controller = _ownCom.GetAIOwner();
	if (!IsValid(controller))
		return;

	AUnitEnemy* enemy = Cast<AUnitEnemy>(controller->GetPawn());
	if (!IsValid(enemy))
		return;

	// 빙의한 몬스터의 탐지범위 수치를 가져온다.
	float range = enemy->GetData()->DetectRange;
	controller->GetBlackboardComponent()->SetValueAsFloat(TEXT("DetectRange"), enemy->GetData()->DetectRange);

	// 플레이어는 월드와 인덱스만 있다면 언제든지 가져올수 있다.
	AUnitPlayer* player = Cast<AUnitPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if(!IsValid(player))
	{
		controller->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), nullptr);
		enemy->SetAttackTarget(nullptr);
		return;
	}
		

	// 플레이어가 해당 탐지범위 내에 있는지 확인한다.
	float distance = FVector::Distance(enemy->GetActorLocation(), player->GetActorLocation());

	if (distance < range)
	{
		// 플레이어가 확인되었으면 타겟(플레이어)을 블랙보드에 기록해야 한다.
		controller->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), player);
		enemy->SetAttackTarget(player);
	}
	else
	{
		// 범위 내에 존재하지 않으면, 타겟을 지워야 한다.
		controller->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), nullptr);
		enemy->SetAttackTarget(nullptr);
	}
}