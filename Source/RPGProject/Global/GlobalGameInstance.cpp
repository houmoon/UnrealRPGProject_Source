#include "GlobalGameInstance.h"

#include "BuffManager.h"
#include "Defines.h"
#include "DialogueManager.h"
#include "DictionaryManager.h"
#include "EnemyDataManager.h"
#include "Engine/DataTable.h"
#include "../Global/ItemManager.h"
#include "RPGProject/Effect/EffectManager.h"
#include "../Global/CooltimeManager.h"
#include "RPGProject/Quest/QuestManager.h"
#include "RPGProject/Unit/Enemy/EnemyModelComponent.h"
#include "RPGProject/Unit/Player/PlayerModelComponent.h"

UGlobalGameInstance::UGlobalGameInstance()
{
	
}

UGlobalGameInstance::~UGlobalGameInstance()
{
}

void UGlobalGameInstance::Init()
{
	Super::Init();

	if (DT_Effect)
		EffectManager::GetInstance()->SetDataTable(DT_Effect);

	if (DT_Enemy)
		EnemyDataManager::GetInstance()->SetDataTable(DT_Enemy);

	if (DT_EquipItem)
		ItemManager::GetInstance()->SetGameItemDataTable(EITEM_TYPE::EQUIPMENT, DT_EquipItem);

	if (DT_UseItem)
	{
		ItemManager::GetInstance()->SetGameItemDataTable(EITEM_TYPE::USE, DT_UseItem);
		CooltimeManager::GetInstance()->Initialize(DT_UseItem);
	}

	if (DT_EtcItem)
		ItemManager::GetInstance()->SetGameItemDataTable(EITEM_TYPE::ETC, DT_EtcItem);

	if(DT_LevelUp)
		DictionaryManager::GetInstance()->InitializeData_Levelup(DT_LevelUp);

	if(DT_Quest)
		QuestManager::GetInstance()->InitDataTable(DT_Quest);

	if (DT_Area)
		DictionaryManager::GetInstance()->InitializeData_Area(DT_Area);

	if (DT_Dialogue)
		DialogueManager::GetInstance()->InitializeData_Dialogue(DT_Dialogue);

	if (DT_Selection)
		DialogueManager::GetInstance()->InitializeData_Selection(DT_Selection);

	if (DT_Buff)
	{
		UBuffManager::GetInstance()->Initialize(DT_Buff);
		CooltimeManager::GetInstance()->Initialize_Buff(DT_Buff);
	}

	UEnemyModelComponent::damageColor = EnemyDamage_Color;
	UPlayerModelComponent::damageColor = PlayerDamage_Color;
	UPlayerModelComponent::recoveryColor = PlayerRecovery_Color;

}
