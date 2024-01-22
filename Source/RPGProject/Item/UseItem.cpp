#include "UseItem.h"

#include "ItemSlot.h"
#include "../Global/CooltimeManager.h"
#include "../Global/ItemManager.h"
#include "../Interfaces/IItemUseCase.h"

void UseItem::Clear()
{
	_amount = 0;
	SetData(ItemManager::GetEmptyUseItemData());

	if (_itemSlot)
		_itemSlot->SetItem(nullptr);
}

void UseItem::OnUse()
{
	if (CooltimeManager::GetInstance()->GetCurrentCooltime(GetItemData()->ID) > 0.f)
		return;

	bool useSucceded = false;

	if (useBehaviors.Num() > 0)
	{
		for (int i = 0; i < useBehaviors.Num(); i++)
		{
			if (useBehaviors[i]->Use())
				useSucceded = true;
		}

	}

	if (useSucceded)
	{
		CooltimeManager::GetInstance()->RegisterCooltime(GetItemData()->ID, GetItemData()->CoolTime);
		SetAmount(GetAmount() - 1);
	}
}

void UseItem::SetData(const FItemData* data)
{
	FUseItemData* useitem = (FUseItemData*) _itemData;

	*useitem  = *(FUseItemData*) data;
	if (useitem->IconAsset.IsPending())
		useitem->IconAsset.LoadSynchronous();

	//UseCase의 타입과 수치를 기반으로 IItemUseCase 인터페이스를 재정의.)

	if(useBehaviors.Num()>0)
	{
		for(int i =0; i< useBehaviors.Num(); i++)
		{
			delete useBehaviors[i];
		}

		useBehaviors.Reset(0);
	}


	FText _description = _itemData->Description;

	if(useitem->UseCases.Num() > 0)
	{
		_description = FText::Format(FText::FromString("{0}\n"), _description);

		for(int32 i=0; i<useitem->UseCases.Num();i++)
		{
			FText useCaseText;

			FString str;
			IItemUseCase* useCase = nullptr;

			switch(useitem->UseCases[i].useCase)
			{
				case EITEM_USECASES::HP_INCREASE:
					FText::FindText(TEXT("ST_ITEM"), TEXT("ITEM_USECASE_HPINCREASE"), useCaseText);
					useCase = new UseCase_HPIncrease(useitem->UseCases[i].amount);
					useBehaviors.Add(useCase);
					break;
				case EITEM_USECASES::MP_INCREASE:
					FText::FindText(TEXT("ST_ITEM"), TEXT("ITEM_USECASE_MPINCREASE"), useCaseText);
					useCase = new UseCase_MPIncrease(useitem->UseCases[i].amount);
					useBehaviors.Add(useCase);
					break;
				case EITEM_USECASES::BUFF:
					useCase = new UseCase_Buff(useitem->UseCases[i].amount);
					useBehaviors.Add(useCase);
					break;
				case EITEM_USECASES::HP_INCREASE_PERCENT:
					break;
				case EITEM_USECASES::MP_INCREASE_PERCENT:
					break;
				default: ;
			}

			useCaseText = FText::Format(useCaseText, useitem->UseCases[i].amount);

			_description = FText::Format(FText::FromString("{0}\n{1}"), _description, useCaseText);
		}

		GetItemData()->Description = _description;
	}



	UpdateSlot();
}
