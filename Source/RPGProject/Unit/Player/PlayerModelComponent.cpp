#include "PlayerModelComponent.h"

#include "Kismet/GameplayStatics.h"
#include "RPGProject/Buff/Buff.h"
#include "RPGProject/Gamemode/Gamemode_Ingame.h"
#include "RPGProject/Global/BuffManager.h"
#include "RPGProject/Global/CooltimeManager.h"
#include "RPGProject/Global/Defines.h"
#include "RPGProject/Global/DictionaryManager.h"
#include "RPGProject/Global/ItemManager.h"
#include "RPGProject/Item/EquipmentSlot.h"
#include "RPGProject/Item/ItemSlot.h"
#include "RPGProject/Item/Inventory/Inventory.h"
#include "RPGProject/Item/Inventory/QuickSlot.h"
#include "RPGProject/Quest/QuestManager.h"
#include "RPGProject/UMG/WD_IngameHUD.h"
#include "RPGProject/UMG/WD_QuickSlot.h"

FColor UPlayerModelComponent::damageColor = FColor::Red;
FColor UPlayerModelComponent::recoveryColor = FColor::Green;

void UPlayerModelComponent::Damage(int32 damage)
{
	float randDmg = FMath::RandRange(_playerData.DEF * 0.5f, _playerData.DEF);
	int32 dmg = (int32) ((damage - randDmg) * 0.5f);

	if(dmg < 0)
		return;

	_playerData.CurHP -= dmg;
	if(_playerData.CurHP < 0)
		_playerData.CurHP = 0;

	UpdateHP();
}

void UPlayerModelComponent::RecoverHP(int32 amount)
{

	_playerData.CurHP += amount;
	if (_playerData.CurHP > _playerData.HP)
		_playerData.CurHP = _playerData.HP;

	UpdateHP();
}

void UPlayerModelComponent::RecoverMP(int32 amount)
{
	_playerData.CurMP += amount;
	if (_playerData.CurMP > _playerData.MP)
		_playerData.CurMP = _playerData.MP;

	UpdateMP();
}

void UPlayerModelComponent::AddExp(int32 exp)
{
	_playerData.CurExp += exp;

	OnAddExp.Broadcast(exp);

	if(_playerData.CurExp >= DictionaryManager::GetInstance()->GetRequiredExp(_playerData.Level))
	{
		int32 level = DictionaryManager::GetInstance()->FindLevel(_playerData.CurExp);
		SetLevel(level);
	}

	UpdateEXP();
}

void UPlayerModelComponent::UseQuickSlotItem(int32 index)
{
	_quickslot->Use(index);
}

void UPlayerModelComponent::SetLevel(const int32 level)
{
	_playerData.Level = level;
	UpdateLevel();
}

void UPlayerModelComponent::AddGold(const int32 gold)
{
	GetInventory()->SetGold(GetInventory()->GetGold() + gold);
	OnAddGold.Broadcast(gold);
}

void UPlayerModelComponent::UseMP(int32 amount)
{
	_playerData.CurMP -= amount;
	if(_playerData.CurMP <0)
		_playerData.CurMP = 0;

	UpdateMP();
}

void UPlayerModelComponent::AddItem(const int32 id)
{
	Item* item = ItemManager::GetInstance()->MakeItem(id);
	AddItem(item);	
}

void UPlayerModelComponent::AddItem(Item* item)
{
	QuestManager::GetInstance()->OnMsgReceived(EQUEST_CLEAR_TYPE::CHECKITEM, item->GetItemData()->ID);

	_inventory->AddItem(item);
	OnItemAdd.Broadcast(item);
}

void UPlayerModelComponent::EnableQuest(const int32 id)
{
	_enabledQuests.Add(id);
	OnRegisterQuest.Broadcast(id);
	//등록된 UI들에게 id가 추가되었다고 알리기
}

void UPlayerModelComponent::AcceptQuest(const int32 id)
{
	if(_enabledQuests.Contains(id))
	{
		_enabledQuests.Remove(id);
	}
	//Create Quest Class & add Quest to _inProgressQuest

	UQuest* newQuest = NewObject<UQuest>();
	newQuest->Initialize(*(QuestManager::GetInstance()->FindQuest(id)));

	_inProgressQuests.Add(id,newQuest);
	OnAcceptQuest.Broadcast(newQuest);

}

void UPlayerModelComponent::FinishQuest(const int32 id)
{
	UQuest** questPtr = _inProgressQuests.Find(id);

	if(!questPtr)
		return;

	UQuest* quest = *questPtr;

	if(quest->GetData().ID == id)
	{
		AddExp(quest->GetData().RewardExp);
		AddGold(quest->GetData().RewardGold);

		for(int32 item : quest->GetData().RewardItem)
		{
			AddItem(item);
		}

		quest->Finish();
		_inProgressQuests.Remove(id);
	}

	_finishedQuests.Add(id);
	OnFinishedQuest.Broadcast(id);
}

void UPlayerModelComponent::RegisterBuff(const int32 id)
{
	UBuff* buff = UBuffManager::GetInstance()->GetBuff(id);
	if(!buff)
		return;

	UBuff** curBuff = _currentBuffs.FindByKey(buff);

	if(!curBuff)
	{
		_currentBuffs.Add(buff);
		CooltimeManager::GetInstance()->RegisterCooltime(id,buff->GetDuration());

		buff->Start();
		buff->OnEnd.AddUObject(this,&UPlayerModelComponent::OnEndBuff);

		OnRegisterBuff.Broadcast(buff);
	}

}

void UPlayerModelComponent::OnEndBuff(UBuff* buff)
{
	if (_currentBuffs.FindByKey(buff))
	{
		_currentBuffs.Remove(buff);
	}
}

void UPlayerModelComponent::AddStat(EBUFF_STAT statType, const float amount)
{
	switch(statType)
	{
	case EBUFF_STAT::ATK:
		GetData()->ATK += amount;
		UpdateStat();
		break;
	case EBUFF_STAT::DEF:
		GetData()->DEF += amount;
		UpdateStat();
		break;
	case EBUFF_STAT::HIT:
		GetData()->HIT += amount;
		UpdateStat();
		break;
	case EBUFF_STAT::DOG:
		GetData()->DOG += amount;
		UpdateStat();
		break;
	case EBUFF_STAT::CRIT:
		GetData()->CRIT += amount;
		UpdateStat();
		break;
	case EBUFF_STAT::STR:
		GetData()->STR += amount;
		UpdateStat();
		break;
	case EBUFF_STAT::INT:
		GetData()->INT += amount;
		UpdateStat();
		break;
	case EBUFF_STAT::DEX:
		GetData()->DEX += amount;
		UpdateStat();
		break;
	case EBUFF_STAT::MAXHP:
		GetData()->HP += amount;
		UpdateHP();
		break;
	case EBUFF_STAT::MAXMP:
		GetData()->MP += amount;
		UpdateMP();
		break;
	case EBUFF_STAT::HP:
		GetData()->CurHP += amount;
		UpdateHP();
		break;
	case EBUFF_STAT::MP:
		GetData()->CurMP += amount;
		UpdateMP();
		break;
	default: ;
	}
}

void UPlayerModelComponent::UpdateEXP()
{
	int32 currentReq = DictionaryManager::GetInstance()->GetRequiredExp(_playerData.Level);

	OnUpdateEXP.Broadcast(_playerData.CurExp - currentReq, DictionaryManager::GetInstance()->GetRequiredExp(_playerData.Level + 1));
}

void UPlayerModelComponent::makeEquipSlot(EITEM_TYPE type)
{
	UEquipmentSlot* newSlot = NewObject<UEquipmentSlot>();
	newSlot->SetType(type);

	_equipSlots.Add(type, newSlot);
}

UEquipmentSlot* UPlayerModelComponent::GetEquipSlot(EITEM_TYPE type)
{
	UEquipmentSlot** slot = _equipSlots.Find(type);
	if(!slot)
		return nullptr;

	return *slot;
}

bool UPlayerModelComponent::isQuestEnabled(const int32 id)
{
	int32* a = _enabledQuests.FindByKey(id);
	if(a)
		return true;
	else
		return false;
}

bool UPlayerModelComponent::isQuestCompleted(const int32 id)
{
	auto a =_inProgressQuests.Find(id);

	if(a)
	{
		if((*a)->GetData().Status == EQUEST_STATUS::COMPLETE)
			return true;
	}
	
	return false;
}

void UPlayerModelComponent::Init(UWorld* world)
{
	//Data Table로부터 데이터 가져오고 구성하기
	FPlayerData* pData = nullptr;

	if (IsValid(_dataBase.DataTable))
	{
		if (_dataBase.RowName.IsNone())
		{
			return;
		}

		pData = _dataBase.DataTable->FindRow<FPlayerData>(_dataBase.RowName, TEXT(""));

		if (nullptr != pData)
		{
			_playerData = *pData;
			_playerData.CurHP = _playerData.HP;
			_playerData.CurMP = _playerData.MP;
		}
	}
	_inventory = NewObject<UInventory>();
	_inventory->Initialize(world, _inventorySize);

	_quickslot = NewObject<UQuickSlot>();
	_quickslot->Initialize(world, _quickslotSize);

	makeEquipSlot(EITEM_TYPE::EQUIPMENT_HELMET);
	makeEquipSlot(EITEM_TYPE::EQUIPMENT_UPPER);
	makeEquipSlot(EITEM_TYPE::EQUIPMENT_LOWER);
	makeEquipSlot(EITEM_TYPE::EQUIPMENT_SHOES);
	makeEquipSlot(EITEM_TYPE::WEAPON);

	QuestManager::GetInstance()->Subscribe(this);
	QuestManager::GetInstance()->Subscribe(this->GetInventory());

	UEquipmentSlot::InitializeSlot();

	//Model 데이터가 준비되었으므로, 구독된 UMG 위젯들에게 Model 데이터와 연결하도록 초기화 신호 발신.
	RegisterUI();

	//Model Update.
	UpdateStat();
	UpdateLevel();
	UpdateHP();
	UpdateMP();
	UpdateEXP();
	UpdateName();
	GetInventory()->UpdateGold();

}

int32 UPlayerModelComponent::GetDamage()
{
	return _playerData.ATK;
}

UPlayerModelComponent::UPlayerModelComponent()
{

	_inventory = nullptr;
}

void UPlayerModelComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UPlayerModelComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Buff Tick
	for (int i = 0; i < _currentBuffs.Num(); i++)
	{
		_currentBuffs[i]->Tick(DeltaTime);
	}

}

void UPlayerModelComponent::InitializeComponent()
{
	Super::InitializeComponent();
}
