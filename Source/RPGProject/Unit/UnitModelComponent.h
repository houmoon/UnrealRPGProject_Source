#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UnitModelComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_OnUpdateName, const FText);

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_OnUpdate_OneInt, const int32);
DECLARE_MULTICAST_DELEGATE_TwoParams(FDelegate_OnUpdate_TwoInt, const int32, const int32);



UCLASS()
class RPGPROJECT_API UUnitModelComponent : public UActorComponent
{
	GENERATED_BODY()

	friend class AUnit;

	//퍼블릭 메시지
	protected:
	virtual void Init(UWorld* world) {}
	virtual int32 GetDamage() { return 0; }
	virtual void Damage(int32 damage);
	virtual void RecoverHP(int32 amount) {}
	virtual void Death() {}

	public:
	FDelegate_OnUpdateName					OnUpdateName;
	FDelegate_OnUpdate_TwoInt				OnUpdateHP;
	FDelegate_OnUpdate_OneInt				OnDeath;


public:	
	UUnitModelComponent();
protected:
	virtual void BeginPlay() override;
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void InitializeComponent() override;

		
};
