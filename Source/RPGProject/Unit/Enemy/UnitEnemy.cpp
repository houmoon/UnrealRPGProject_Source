#include "UnitEnemy.h"

#include "EnemyModelComponent.h"
#include "behaviortree/blackboardcomponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "RPGProject/AI/EnemyMeleeAIController.h"
#include "RPGProject/DataBase/UnitDB.h"
#include "RPGProject/Global/Defines.h"
#include "RPGProject/Quest/QuestManager.h"
#include "RPGProject/UMG/WD_EnemyInfo.h"
#include "RPGProject/Unit/Player/PlayerModelComponent.h"
#include "RPGProject/Unit/Player/UnitPlayer.h"

FVector AUnitEnemy::GetLocalMoveDir()
{
	return Super::GetLocalMoveDir();
}

const EENEMY_STATE& AUnitEnemy::GetState()
{
	return _enemyModel->_state;
}

const FEnemyData* const AUnitEnemy::GetData()
{
	return &_enemyModel->_enemyData;
}

UBehaviorTree* const AUnitEnemy::GetBehaviourTree()
{
	return _enemyModel->_behaviorTree;
}

UBlackboardData* const AUnitEnemy::GetBlackBoard()
{
	return _enemyModel->_blackBoardData;
}

void AUnitEnemy::Attack()
{
	if (!IsValid(GetMesh()->GetAnimInstance()))
		return;

	if (_attackMeleeMontage)
		GetMesh()->GetAnimInstance()->Montage_Play(_attackMeleeMontage,_enemyModel->_enemyData.AtkSpeed);

}

void AUnitEnemy::Damage(int32 damage)
{
	displayDamage(damage, UEnemyModelComponent::damageColor);

	_enemyModel->Damage(damage);

	if(_hitReactionMontage)
	{
		GetMesh()->GetAnimInstance()->Montage_Play(_hitReactionMontage,1.f,EMontagePlayReturnType::MontageLength,0.f,false);
	}
}

void AUnitEnemy::Death(const int32 ID)
{
	QuestManager::GetInstance()->OnMsgReceived(EQUEST_CLEAR_TYPE::KILL, ID);

	_widgetComponent->SetVisibility(false);

	AEnemyMeleeAIController* pAIController = Cast<AEnemyMeleeAIController>(GetController());

	if (IsValid(pAIController))
	{
		pAIController->UnPossess();
		pAIController->Destroy();
	}

	GetCapsuleComponent()->SetEnableGravity(false);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("NoCollision"));

	if(_deathMontage)
		GetMesh()->GetAnimInstance()->Montage_Play(_deathMontage,1.f);

	_widgetComponent->SetVisibility(false);

}

void AUnitEnemy::DamageToTarget()
{
	if(nullptr != _attackTarget)
	{
		_attackTarget->Damage(_enemyModel->GetDamage());
	}
}

void AUnitEnemy::Burn()
{
	_isBurning = true;
}

void AUnitEnemy::GiveItemsToPlayer()
{
	AUnitPlayer* player = AUnitPlayer::CurrentPlayer;

	if (IsValid(player))
	{
		TArray<int32> rewards = _enemyModel->_enemyData.RewardIDs;

		for(int i=0; i<rewards.Num(); i++)
		{
			player->AddItem(rewards[i]);
		}

		player->GetModel()->AddGold(_enemyModel->_enemyData.RewardGold);
		player->GetModel()->AddExp(_enemyModel->_enemyData.RewardEXP);

	}
}

void AUnitEnemy::SetState(EENEMY_STATE state)
{
	_enemyModel->SetState(state);
}

AUnitEnemy::AUnitEnemy() : _attackTarget(nullptr), _enemyModel(nullptr), _widgetComponent(nullptr) , _isBurning(false), _burnIntense(-0.3f)
{
	PrimaryActorTick.bCanEverTick = true;

	//컴포넌트 초기화
	_widgetComponent = CreateDefaultSubobject<UWidgetComponent>(L"Info Widget");
	_widgetComponent->SetupAttachment(GetCapsuleComponent());

	//모델 초기화
	_enemyModel = CreateDefaultSubobject<UEnemyModelComponent>(L"Enemy Model");

	//AI 컨트롤러 설정
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AEnemyMeleeAIController::StaticClass();



}

void AUnitEnemy::BeginPlay()
{
	Super::BeginPlay();
	_enemyModel->Init(GetMesh()->GetWorld());
	GetCharacterMovement()->MaxWalkSpeed = _enemyModel->_enemyData.MoveSpeed;
	GetMesh()->SetScalarParameterValueOnMaterials(TEXT("Burn Intense"), _burnIntense);

	_enemyModel->OnDeath.AddUObject(this,&AUnitEnemy::Death);


	UWD_EnemyInfo* enemyInfo = Cast<UWD_EnemyInfo>(_widgetComponent->GetWidget());

	if(IsValid(enemyInfo))
	{
		enemyInfo->SetDelegate(this);
	}

	AAIController* controller = Cast<AAIController>(GetController());
	if(IsValid(controller))
	{
		//AI 컨트롤러의 블랙보드 데이터를 세팅.
		controller->GetBlackboardComponent()->SetValueAsFloat(FName("DetectRange"), _enemyModel->_enemyData.DetectRange);
		controller->GetBlackboardComponent()->SetValueAsFloat(FName("AttackRange"), _enemyModel->_enemyData.AttackRange);
		controller->GetBlackboardComponent()->SetValueAsVector(FName("SpawnPos"),GetActorLocation());
	}

}

void AUnitEnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(FVector::Dist(GetActorLocation(), AUnitPlayer::CurrentPlayer->GetActorLocation()) <= _enemyModel->_enemyData.DetectRange + 1.f )
		_widgetComponent->SetVisibility(true);
	else
		_widgetComponent->SetVisibility(false);

	if(_isBurning)
	{
		_burnIntense += DeltaSeconds * 0.8f;
		GetMesh()->SetScalarParameterValueOnMaterials(TEXT("Burn Intense"), _burnIntense);

		if(_burnIntense > 1.f)
		{
			Destroy();
		}
			
	}


}
