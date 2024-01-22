#include "EnemyAnimInstance.h"

#include "EnemyModelComponent.h"
#include "UnitEnemy.h"

void UEnemyAnimInstance::AnimNotify_DamageToTarget()
{
	_enemy->DamageToTarget();
}

void UEnemyAnimInstance::AnimNotify_Burn()
{
	_enemy->Burn();
}

void UEnemyAnimInstance::AnimNotify_GiveItem()
{
	_enemy->GiveItemsToPlayer();
}

UEnemyAnimInstance::UEnemyAnimInstance()
{
}

void UEnemyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	AUnitEnemy* enemy = Cast<AUnitEnemy>(GetOwningActor());

	if (IsValid(enemy))
		_enemy = enemy;
}

void UEnemyAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UEnemyAnimInstance::NativeUpdateAnimation(float deltaTime)
{
	Super::NativeUpdateAnimation(deltaTime);

	if (IsValid(_enemy))
	{
		_state = _enemy->GetState();
	}
}
