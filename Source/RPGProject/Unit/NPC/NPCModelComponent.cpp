#include "NPCModelComponent.h"

#include "RPGProject/Global/Debug.h"
#include "RPGProject/Global/Defines.h"

void UNPCModelComponent::Init(UWorld* world)
{
	FNpcData* pData = nullptr;

	if (IsValid(_dataBase.DataTable))
	{
		if (_dataBase.RowName.IsNone())
		{
			return;
		}

		pData = _dataBase.DataTable->FindRow<FNpcData>(_dataBase.RowName, TEXT(""));

		if (nullptr != pData)
		{
			_data = *pData;
		}
	}

}

UNPCModelComponent::UNPCModelComponent()
{
}

void UNPCModelComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UNPCModelComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UNPCModelComponent::InitializeComponent()
{
	Super::InitializeComponent();
}
