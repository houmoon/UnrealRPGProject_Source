

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WD_Buff.generated.h"

class UBuff;
class UImage;
class UTextBlock;


UCLASS()
class RPGPROJECT_API UWD_Buff : public UUserWidget
{
	GENERATED_BODY()

	private:
	int32 _id;
	float _cooltime;

	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = true))
	UImage*		_image = nullptr;

	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = true))
	UImage*		_cooltimeImage;

	UPROPERTY(EditAnywhere)
	UMaterialInterface*		_cooltimeMT = nullptr;
	UMaterialInstanceDynamic* _cooltimeMTInstance = nullptr ;

	public:
	UFUNCTION()
	void Delete(UBuff* buff);

	void SetValue(int32 ID, int32 Cooltime, UTexture2D* Texture);

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& geometry, float deltaTime) override;
};
