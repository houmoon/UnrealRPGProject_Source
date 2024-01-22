#pragma once

#include "CoreMinimal.h"
#include <List>

#include "RPGProject/DataBase/QuestDB.h"
#include "RPGProject/DataBase/UnitDB.h"
#include "RPGProject/Enums/BuffEnums.h"
#include "RPGProject/Item/ItemSlot.h"
#include "RPGProject/Unit/UnitModelComponent.h"

#include "PlayerModelComponent.generated.h"

class UBuff;
class UQuest;
class UInventory;
class UEquipmentSlot;
class DictionaryManager;
class UQuickSlot;
class Item;

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_OnAcceptQuest, UQuest*);

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_OnRegisterBuff, UBuff*);
DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_OnRegisterUI, UPlayerModelComponent*);
DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_OnItemAdd, Item*);
DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_OnUpdateStat, const FPlayerData&);

UCLASS()
class RPGPROJECT_API UPlayerModelComponent : public UUnitModelComponent
{
	GENERATED_BODY()

	friend class AUnitPlayer;
	
	//플레이어의 데이터
	private:
	UPROPERTY(EditAnywhere,category = "Player Data", meta = (AllowPrivateAccess = "true"))
	FPlayerData _playerData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data", meta = (RowType = "PlayerData", AllowPrivateAccess = "true"))
	FDataTableRowHandle _dataBase;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data", meta = (AllowPrivateAccess = "true"))
	int32 _inventorySize = 64;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data", meta = (AllowPrivateAccess = "true"))
	int32 _quickslotSize = 8;

	UPROPERTY()
	TArray<int32> _enabledQuests;

	UPROPERTY()
	TMap<int32,UQuest*> _inProgressQuests;

	UPROPERTY()
	TArray<int32> _finishedQuests;


	//Inventory & Slots
	UPROPERTY()
	UInventory* _inventory;
	UPROPERTY()
	UQuickSlot* _quickslot;

	UPROPERTY()
	TMap<EITEM_TYPE,UEquipmentSlot*> _equipSlots;

	void makeEquipSlot(EITEM_TYPE type);

	//Buff
	UPROPERTY()
	TArray<UBuff*> _currentBuffs;



	public:
	static FColor		damageColor;
	static FColor		recoveryColor;

	UEquipmentSlot* GetEquipSlot(EITEM_TYPE type);
	UQuickSlot* GetQuickSlot() {return _quickslot; }
	UInventory*	GetInventory()	{ return _inventory; }
	FPlayerData*	GetData()		{ return &_playerData; }



	public:
	bool isQuestEnabled(const int32 id);
	bool isQuestCompleted(const int32 id);

	void RegisterUI() { OnRegisterUI.Broadcast(this); }
	virtual void Init(UWorld* world) override;
	virtual int32 GetDamage() override;
	virtual void Damage(int32 damage) override;
	virtual void RecoverHP(int32 amount) override;
	void RecoverMP(int32 amount);
	void AddExp (int32 exp);
	void UseMP(int32 amount);
	 
	void UseQuickSlotItem(int32 index);

	void SetLevel(const int32 level);
	void AddGold(const int32 gold);
	void AddItem(const int32 id);
	void AddItem(Item* item);

	void EnableQuest(const int32 id);

	UFUNCTION(BlueprintCallable)
	void AcceptQuest(const int32 id);
	void FinishQuest(const int32 id);

	void RegisterBuff(const int32 id);
	UFUNCTION()
	void OnEndBuff(UBuff* buff);

	void AddStat(EBUFF_STAT statType, const float amount);


	//Delegates
	public:
	FDelegate_OnUpdate_OneInt		OnAddExp;
	FDelegate_OnUpdate_OneInt		OnAddGold;
	FDelegate_OnItemAdd				OnItemAdd;
	FDelegate_OnRegisterUI			OnRegisterUI;

	FDelegate_OnUpdate_TwoInt		OnUpdateMP;
	FDelegate_OnUpdate_TwoInt		OnUpdateEXP;
	FDelegate_OnUpdate_OneInt		OnUpdateLevel;

	FDelegate_OnUpdateStat			OnUpdateStat;

	FDelegate_OnUpdate_OneInt		OnRegisterQuest;
	FDelegate_OnUpdate_OneInt		OnFinishedQuest;
	FDelegate_OnAcceptQuest			OnAcceptQuest;
	FDelegate_OnRegisterBuff		OnRegisterBuff;

	void UpdateHP() { OnUpdateHP.Broadcast(_playerData.CurHP,_playerData.HP);}
	void UpdateMP() { OnUpdateMP.Broadcast(_playerData.CurMP, _playerData.MP);}
	void UpdateEXP();
	void UpdateLevel() { OnUpdateLevel.Broadcast(_playerData.Level); }
	void UpdateName() {OnUpdateName.Broadcast(_playerData.Name);}
	void UpdateStat() { OnUpdateStat.Broadcast(_playerData); }

	public:
	UPlayerModelComponent();
	protected:
	virtual void BeginPlay() override;
	public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void InitializeComponent() override;

};
