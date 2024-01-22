#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "RPGProject/DataBase/InputDB.h"
#include "DAInputAction.generated.h"


UCLASS()
class RPGPROJECT_API UDAInputAction : public UDataAsset
{
	GENERATED_BODY()

	public:
	UPROPERTY(EditDefaultsOnly, Category = "Character Input Components", Meta = (DisplayName = "Player InputAction Binds"))
	TArray<FInputContextData> PlayerInputDatas;

	UPROPERTY(EditDefaultsOnly, Category = "Character Input Components", Meta = (DisplayName = "UI InputAction Binds"))
	TArray<FUIInputContextData> UIInputDatas;

};
