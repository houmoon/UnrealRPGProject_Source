#pragma once

#include "CoreMinimal.h"
#include "RPGProject/DataBase/UnitDB.h"
#include "RPGProject/Unit/UnitModelComponent.h"
#include "NPCModelComponent.generated.h"

UCLASS()
class RPGPROJECT_API UNPCModelComponent : public UUnitModelComponent
{
	GENERATED_BODY()

	//퍼블릭 메시지
	public:
	virtual void Init(UWorld* world) override;

	private:
	UPROPERTY(EditAnywhere, category = "NPC Data", meta = (AllowPrivateAccess = "true"))
	FNpcData _data;

	UPROPERTY(EditAnywhere, category = "NPC Data", meta = (AllowPrivateAccess = "true"))
	FDataTableRowHandle _dataBase;

public:	
	UNPCModelComponent();
	FNpcData* GetData() { return &_data; }


protected:
	virtual void BeginPlay() override;
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void InitializeComponent() override;

		
};
