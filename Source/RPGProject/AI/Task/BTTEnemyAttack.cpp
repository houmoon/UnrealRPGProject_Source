// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTEnemyAttack.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include "AIController.h"
#include <Kismet/KismetMathLibrary.h>

#include "RPGProject/Enums/UnitEnums.h"
#include "RPGProject/Unit/Enemy/EnemyModelComponent.h"
#include "RPGProject/Unit/Enemy/UnitEnemy.h"
#include "RPGProject/Unit/Player/UnitPlayer.h"

UBTTEnemyAttack::UBTTEnemyAttack()
{
	//Tick을 활성화.
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTEnemyAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	_enemy = Cast<AUnitEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	_target = Cast<AUnit>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(_targetKey.SelectedKeyName));


	AUnitPlayer* pCharacterBase = Cast<AUnitPlayer>(_target);

	if(!IsValid(_enemy))
	{
		return EBTNodeResult::Failed;
	}

	if (!IsValid(_target))
	{
		return EBTNodeResult::Failed;
	}

	AAIController* pAIController = OwnerComp.GetAIOwner();
	pAIController->StopMovement();


	if (EENEMY_STATE::MELEE_ATTACK != _enemy->GetState())
	{
		_enemy->SetState(EENEMY_STATE::MELEE_ATTACK);
		_enemy->Attack();
	}

	if (!_rangeKey.IsNone())
	{
		m_range = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(_rangeKey.SelectedKeyName);
	}

	return EBTNodeResult::InProgress;
}

EBTNodeResult::Type UBTTEnemyAttack::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	_enemy = Cast<AUnitEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	if (IsValid(_enemy))
	{
		_enemy->SetState(EENEMY_STATE::IDLE);
		_enemy->StopAnimMontage();
	}

	return EBTNodeResult::Aborted;
}

void UBTTEnemyAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	//Monster = Cast<AMonsterBase>(OwnerComp.GetAIOwner()->GetPawn());
	//_target = Cast<ACharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(_targetKey.SelectedKeyName));
	if (IsValid(_enemy) && IsValid(_target))
	{
		FRotator rot = UKismetMathLibrary::FindLookAtRotation(_enemy->GetActorLocation(), _target->GetActorLocation());
		_enemy->SetActorRotation(rot);

		float distance = FVector::Distance(_target->GetActorLocation(), _enemy->GetActorLocation());

		if (distance > m_range)
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
			return;
		}
			
	}


}
