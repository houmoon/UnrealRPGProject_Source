// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTEnemyTrace.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

#include "RPGProject/Enums/UnitEnums.h"
#include "RPGProject/Unit/Enemy/EnemyModelComponent.h"
#include "RPGProject/Unit/Enemy/UnitEnemy.h"


UBTTEnemyTrace::UBTTEnemyTrace()
{
	//Tick을 활성화.
	bNotifyTick = true;

	//블랙보드 컴포넌트로서 키를 넣어줄때, 키를 정해줄 수 있는 종류를 제한할 수 있다.
	_targetKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTTEnemyTrace, _targetKey), AActor::StaticClass());
	_recentTargetPosKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTEnemyTrace, _recentTargetPosKey));
}

EBTNodeResult::Type UBTTEnemyTrace::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//추적 대상이 없다면 취소
	if (_targetKey.IsNone() || _recentTargetPosKey.IsNone())
		return EBTNodeResult::Failed;

	AAIController* pController = OwnerComp.GetAIOwner();
	ACharacter* pCharacter = Cast<ACharacter>(pController->GetBlackboardComponent()->GetValueAsObject(_targetKey.SelectedKeyName));

	//추적 대상이 캐릭터가 아니라면 취소
	if(!IsValid(pCharacter))
		return EBTNodeResult::Failed;
	else
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName("TraceTarget"), pCharacter); //추적 대상을 임시로 저장.

	// 네비메시가 깔려있는 곳에서, 목적지를 향해 길찾기 알고리즘을 통한 최초 이동을 수행.
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(pController, pCharacter->GetActorLocation());

	//현재 추적대상의 위치(최근 이동 목적지)를 블랙보드에 기록해둔다.
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(_recentTargetPosKey.SelectedKeyName, pCharacter->GetActorLocation());

	//재계산 범위를 가져온다.
	//_recalcutateRange = pController->GetBlackboardComponent()->GetValueAsFloat(m_RecalcutateRangeKey.SelectedKeyName);

	//추적상태에 들어오면, 몬스터를 이동상태로 전환.
	AUnitEnemy* pEnemy = Cast<AUnitEnemy>(pController->GetPawn());
	pEnemy->SetState(EENEMY_STATE::MOVE);


	return EBTNodeResult::InProgress;
}

//매 프레임마다 실행. 변화를 감지하는데 유용.
void UBTTEnemyTrace::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (_targetKey.IsNone() || _recentTargetPosKey.IsNone())
	{
		//Inprogress 상태를 중단
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	// 추적중에 추적대상이 공격범위 안으로 들어오면, 추적 상태를 성공으로 중단시켜서
	// 트리가 다시 루트부터 시작될 수 있게 한다.
	
	// 임시로 저장된 추적 대상을 가져옴. (m_TargetKey를 가져오면 0.5초 간격 서비스에 의해 없어질수도 있기 때문.
	ACharacter* pTarget = Cast<ACharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("TraceTarget")));
	if (!IsValid(pTarget))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}


	//공격 범위를 가져옴.
	float fAttRange = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(L"AttackRange");

	//몬스터 액터를 가져옴.
	AAIController* pController = OwnerComp.GetAIOwner();
	AUnitEnemy* pEnemy = Cast<AUnitEnemy>(pController->GetPawn());
	if (!IsValid(pEnemy))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	pEnemy->StopAnimMontage();

	//공격 범위 내에 들어왔다면, 성공을 반환시켜서 행동트리가 Patrol로 가는것을 막음.
	float Distance = FVector::Distance(pTarget->GetActorLocation(), pEnemy->GetActorLocation());
	if (Distance < fAttRange)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}

	//추격 범위 외에 있다면, 실패를 반환시켜서 행동트리가 Patrol로 가게 한다.
	float fDttRange = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(L"DetectRange");
	if (Distance >= fDttRange)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}


	//현재 타겟의 위치가 몬스터의 이동 목적지와 재계산거리가 멀어진다면
	FVector vRecentDest = OwnerComp.GetBlackboardComponent()->GetValueAsVector(_recentTargetPosKey.SelectedKeyName);
	
	if (_recalcutateRange < FVector::Distance(pEnemy->GetActorLocation(), vRecentDest))
	{
		//추적 위치를 재설정
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(pController, pTarget->GetActorLocation());
		
		//추적중인 위치를 저장.
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(_recentTargetPosKey.SelectedKeyName, pTarget->GetActorLocation());

	}
}


