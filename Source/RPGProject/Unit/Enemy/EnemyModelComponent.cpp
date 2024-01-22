#include "EnemyModelComponent.h"

#include "RPGProject/Enums/UnitEnums.h"
#include "RPGProject/Global/Defines.h"
#include "RPGProject/Global/EnemyDataManager.h"

FColor UEnemyModelComponent::damageColor = FColor::Red;

int32 UEnemyModelComponent::GetDamage()
{
	return _enemyData.ATK;
}

void UEnemyModelComponent::Init(UWorld* world)
{
	if (IsValid(_dataBase.DataTable))
	{
		if (_dataBase.RowName.IsNone())
		{
			return;
		}

		_enemyData = *EnemyDataManager::GetInstance()->GetEnemyData(FCString::Atoi(*_dataBase.RowName.ToString()));
		OnUpdateName.Broadcast(_enemyData.Name);

	}
}

void UEnemyModelComponent::Damage(int32 damage)
{
	float randDmg = FMath::RandRange(_enemyData.DEF * 0.5f, _enemyData.DEF);
	int32 dmg = (int32) ((damage - randDmg) * 0.5f);

	if (dmg < 0)
		return;

	_enemyData.CurHP -= dmg;
	if(_enemyData.CurHP < 0)
		Death();

	OnUpdateHP.Broadcast(_enemyData.CurHP,_enemyData.HP);
}

void UEnemyModelComponent::Death()
{
	_enemyData.CurHP = 0;
	_state = EENEMY_STATE::DEATH;
	OnDeath.Broadcast(_enemyData.ID);
}

// Sets default values for this component's properties
UEnemyModelComponent::UEnemyModelComponent() : _state(EENEMY_STATE::IDLE)
{
	//PrimaryComponentTick.bCanEverTick = true;

	
}


// Called when the game starts
void UEnemyModelComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


// Called every frame
void UEnemyModelComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

void UEnemyModelComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

