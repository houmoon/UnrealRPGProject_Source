#include "WD_EnemyInfo.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "RPGProject/Global/Defines.h"

#include "RPGProject/Unit/Enemy/EnemyModelComponent.h"
#include "RPGProject/Unit/Enemy/UnitEnemy.h"

void UWD_EnemyInfo::InitializeElements()
{
	_healthbar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HealthBar")));
	_name = Cast<UTextBlock>(GetWidgetFromName(TEXT("Name")));
}

void UWD_EnemyInfo::SetDelegate(AUnitEnemy* enemy)
{
	InitializeElements();

	enemy->GetModel()->OnUpdateHP.AddUObject(this,&UWD_EnemyInfo::SetHealthBarValue);
	enemy->GetModel()->OnUpdateName.AddUObject(this,&UWD_EnemyInfo::SetName);

	enemy->GetModel()->UpdateHP();
	enemy->GetModel()->UpdateName();
}

void UWD_EnemyInfo::NativeConstruct()
{
	Super::NativeConstruct();

	_healthbar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HealthBar")));
	_name = Cast<UTextBlock>(GetWidgetFromName(TEXT("Name")));

	
}

void UWD_EnemyInfo::NativeTick(const FGeometry& geometry, float deltaTime)
{
	Super::NativeTick(geometry, deltaTime);

}
