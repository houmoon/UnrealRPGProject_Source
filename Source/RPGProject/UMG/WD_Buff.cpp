#include "WD_Buff.h"
#include "Components/Image.h"
#include "Components/PanelWidget.h"
#include "RPGProject/Global/CooltimeManager.h"


void UWD_Buff::Delete(UBuff* buff)
{
	RemoveFromParent();
}

void UWD_Buff::SetValue(int32 ID, int32 Cooltime, UTexture2D* Texture)
{
	_id = ID;
	_cooltime = Cooltime;

	if(Texture)
		_image->SetBrushFromTexture(Texture);
}

void UWD_Buff::NativeConstruct()
{
	Super::NativeConstruct();

	if(_cooltimeMT)
	{
		_cooltimeMTInstance = UMaterialInstanceDynamic::Create(_cooltimeMT, this);
		_cooltimeImage->SetBrushFromMaterial(_cooltimeMTInstance);
		_cooltimeMTInstance->SetScalarParameterValue("Percent", 0.f);
	}
}

void UWD_Buff::NativeTick(const FGeometry& geometry, float deltaTime)
{
	Super::NativeTick(geometry,deltaTime);
	if (_cooltimeMTInstance && _id != 0)
	{
		float currentcooltime = CooltimeManager::GetInstance()->GetCurrentCooltime(_id);

		float percent = currentcooltime / _cooltime;

		percent = 1.0f - percent;
		if (percent <= 0.f || percent >= 1.f)
			_cooltimeImage->SetVisibility(ESlateVisibility::Hidden);
		else
		{
			_cooltimeImage->SetVisibility(ESlateVisibility::Visible);
			_cooltimeMTInstance->SetScalarParameterValue("Percent", percent);
		}
	}
	else
		_cooltimeImage->SetVisibility(ESlateVisibility::Hidden);
}
