#pragma once
#include "InputAction.h"

#include "RPGProject/Enums/InputEnums.h"
#include "InputDB.generated.h"

USTRUCT(Atomic, BlueprintType)
struct FInputContextData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	EINPUT_TYPE_PLAYER Type;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UInputAction> Action;
};

USTRUCT(Atomic, BlueprintType)
struct FUIInputContextData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	EINPUT_TYPE_UI Type;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UInputAction> Action;
};